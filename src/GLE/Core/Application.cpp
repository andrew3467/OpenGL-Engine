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

        const float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f
        };

        const uint32_t indices[] = {
                0, 1, 2
        };

        uint32_t VAO, VBO, EBO;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
        glEnableVertexAttribArray(0);

        Shader shader("../assets/shaders/Standard.glsl");


        while (mRunning) {
            for(auto layer : mLayerStack.GetLayers()) {
                layer->OnUpdate();
                layer->OnRender();

                shader.Bind();
                shader.SetFloat3("uColor", {1.0f, 0.0f, 1.0f});
                glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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