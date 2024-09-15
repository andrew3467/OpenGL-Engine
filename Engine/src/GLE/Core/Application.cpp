//
// Created by Andrew Graser on 7/28/2024.
//


#include "Core/Application.h"
#include "Core/Window.h"

#include "Events/Event.h"

#include "Renderer/Renderer.h"

#include "Time.h"
#include "Scene/Scene.h"
#include "UI/ImGuiLayer.h"


#include "GLFW/glfw3.h"
#include "glm/gtx/string_cast.hpp"


#include <string>
#include <functional>

#include "Renderer/Shader.h"

#define BIT(x) (1 << x)


namespace GLE {
    Application* Application::sInstance = nullptr;

    Application::Application() {
        sInstance = this;
    }

    Application::~Application() {
        for(auto& layer : mLayerStack.GetLayers()) {
            layer->OnDestroy();
        }

        mImguiLayer->OnDestroy();
    }


    void Application::Run() {
        GLE_INFO("Running Application");
        mRunning = true;

        Time::Init();

        mWindow = Window::Create({1280, 720, "GL Engine"});
        mWindow->SetEventCallback(GLE_BIND_EVENT_FUNC(Application::OnEvent));

        Renderer::Init();

        //Init after opengl bindings are generated
        Shader::Init();

        Renderer::SetClearColor(0.2, 0.2, 0.2);

        GLE_INFO("Setting up ImGui");
        mImguiLayer = std::make_unique<ImGuiLayer>();
        mImguiLayer->OnCreate();

        //Init layers
        for(auto layer : mLayerStack.GetLayers()) {
            GLE_INFO("Init layer: {0}", layer->GetName());
            layer->OnRun();
        }
        GLE_INFO("Init Layer {0}", mImguiLayer->GetName());
        mImguiLayer->OnRun();


        while (mRunning) {
            for(auto layer : mLayerStack.GetLayers()) {
                layer->OnUpdate(Time::GetTime());
                layer->OnRender();
            }

            //Render ImGui
            mImguiLayer->Begin();

            for(auto layer : mLayerStack.GetLayers()) {
                layer->OnImGuiRender();
            }

            mImguiLayer->End();


            mWindow->Update();

            Renderer::Clear();

            Time::Update();
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent &e) {
        mRunning = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent &e) {
#ifdef GLE_PLATFORM_GLFW
        glfwSetWindowSize((GLFWwindow*)mWindow->GetNativeWindow(), e.GetWidth(), e.GetHeight());
        Renderer::UpdateViewport(0, 0, e.GetWidth(), e.GetHeight());
#endif
        return true;
    }

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(GLE_BIND_EVENT_FUNC(Application::OnWindowClosed));
        dispatcher.Dispatch<WindowResizeEvent>(GLE_BIND_EVENT_FUNC(Application::OnWindowResize));

        for(auto it : mLayerStack.GetLayers()) {
            if(e.Handled) break;

            (*it).OnEvent(e);
        }
    }
}