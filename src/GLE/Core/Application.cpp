//
// Created by Andrew Graser on 7/28/2024.
//


#include "Core/Application.h"
#include "Core/Window.h"

#include "Renderer/Renderer.h"

#include "Events/MouseEvent.h"

//temp
#include "GLFW/glfw3.h"


#include "Glad/glad.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

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


        mWindow = Window::Create({1280, 720, "GL Engine"});
        mWindow->SetEventCallback(GLE_BIND_EVENT_FUNC(Application::OnEvent));

        Renderer::Init();

        Renderer::SetClearColor(0.2, 0.2, 0.2);

        while (mRunning) {
            for(auto layer : mLayerStack.GetLayers()) {
                layer->OnUpdate();
                layer->OnRender();

                mWindow->Update();

                Renderer::Clear();
            }
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