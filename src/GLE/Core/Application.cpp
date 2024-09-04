//
// Created by Andrew Graser on 7/28/2024.
//


#include "Core/Application.h"
#include "Core/Window.h"

#include "Renderer/Renderer.h"

#include "Events/MouseEvent.h"

//temp
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "GLFW/glfw3.h"


#include "Glad/glad.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Camera.h"
#include "glm/gtx/string_cast.hpp"
#include "Time.h"
#include "Scene/Scene.h"
#include "Scene/ECS/Entity.h"
#include "UI/ImGuiLayer.h"

namespace GLE {
    Application* Application::sInstance = nullptr;


    Application *Application::Create(Layer *startLayer) {
        Log::Init();

        auto app = new Application();
        app->PushLayer(startLayer);

        return app;
    }

    Application::Application() {
        sInstance = this;
    }

    Application::~Application() {

    }



    void Application::Run() {
        GLE_INFO("Running Application");
        mRunning = true;

        Time::Init();

        mWindow = Window::Create({1280, 720, "GL Engine"});
        mWindow->SetEventCallback(GLE_BIND_EVENT_FUNC(Application::OnEvent));

        Renderer::Init();

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

        static bool demoWindow = true;

        while (mRunning) {
            for(auto layer : mLayerStack.GetLayers()) {
                layer->OnUpdate(Time::GetTime());
                layer->OnRender();
            }

            //Render ImGui
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            mImguiLayer->OnRender();

            if(demoWindow) {
                ImGui::ShowDemoWindow(&demoWindow);
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


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
