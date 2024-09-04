//
// Created by Andrew Graser on 7/28/2024.
//

#ifndef OPENGL_ENGINE_APPLICATION_H
#define OPENGL_ENGINE_APPLICATION_H

#include "LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace GLE {
    class Scene;

    class Application {
    public:
        inline static Application& Get() {return *sInstance;}
    private:
        static Application* sInstance;


    public:
        static Application* Create(Layer* startLayer);

        Application();
        ~Application();

        const Window& GetWindow() const {return *mWindow;}

        void Run();

        void OnEvent(Event &e);

        inline void Stop() {mRunning = false;}

        inline void PushLayer(Layer* layer) {mLayerStack.Push(layer);}

    private:
        bool OnWindowClosed(WindowCloseEvent &e);
        bool OnWindowResize(WindowResizeEvent &e);

    private:
        bool mRunning = false;

        LayerStack mLayerStack;


        std::shared_ptr<Window> mWindow;
    };
}

#endif //OPENGL_ENGINE_APPLICATION_H
