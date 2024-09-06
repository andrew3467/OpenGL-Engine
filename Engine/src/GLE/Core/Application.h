//
// Created by Andrew Graser on 7/28/2024.
//

#pragma once


#include "LayerStack.h"
#include "Window.h"
#include "UI/ImGuiLayer.h"

#include "Events/ApplicationEvent.h"

namespace GLE {
    class Scene;

    class Application {
    public:
        static Application& Get() {return *sInstance;}
    private:
        static Application* sInstance;


    public:
        Application();
        ~Application();

        const Window& GetWindow() const {return *mWindow;}

        void Run();

        void OnEvent(Event &e);

        void Stop() {mRunning = false;}

        void PushLayer(Layer* layer) {mLayerStack.Push(layer);}

    private:
        bool OnWindowClosed(WindowCloseEvent &e);
        bool OnWindowResize(WindowResizeEvent &e);

    private:
        bool mRunning = false;

        LayerStack mLayerStack;
        std::unique_ptr<ImGuiLayer> mImguiLayer;


        std::shared_ptr<Window> mWindow;
    };

    Application* CreateApplication();
}
