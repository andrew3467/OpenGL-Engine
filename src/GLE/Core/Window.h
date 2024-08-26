//
// Created by Andrew Graser on 7/28/2024.
//

#ifndef OPENGL_ENGINE_WINDOW_H
#define OPENGL_ENGINE_WINDOW_H

#include "Events/ApplicationEvent.h"

//class Event;
class GLFWwindow;

namespace GLE {
    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        struct WindowProps {
            uint32_t Width = 1280;
            uint32_t Height = 720;
            std::string Title = "GLE Engine";
        };

    public:
        static std::shared_ptr<Window> Create(const WindowProps& props);

    public:
        Window(const WindowProps& props);
        ~Window();

        void Update();

        inline void* GetNativeWindow() const {return mWindowContainer.nativeWindow;}
        inline uint32_t GetWidth() const {return mData.Width;}


        inline uint32_t GetHeight() const {return mData.Height;}

        inline void SetEventCallback(const EventCallbackFn &callback) {
            mData.EventCallback = callback;
        }
    public:
        void SetupCallbacks();


    private:
        struct WindowContainer {
            void* nativeWindow;
            void* context;
        } mWindowContainer;

        struct WindowData {
            uint32_t Width;
            uint32_t Height;
            std::string Title;
            bool VSYNC = true;

            EventCallbackFn EventCallback;
        };

        WindowData mData;
    };
}

#endif //OPENGL_ENGINE_WINDOW_H
