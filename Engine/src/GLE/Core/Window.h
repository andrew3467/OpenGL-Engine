//
// Created by Andrew Graser on 7/28/2024.
//

#pragma once


//class Event;
class GLFWwindow;

namespace GLE {
    class Event;

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        struct WindowProps {
            uint32_t Width = 1280;
            uint32_t Height = 720;
            std::string Title = "GLE Engine";
        };
        static std::shared_ptr<Window> Create(const WindowProps& props);

        Window(const WindowProps& props);
        ~Window();

        void Update();

        void* GetNativeWindow() const {return mWindowContainer.nativeWindow;}

        uint32_t GetWidth() const {return mData.Width;}
        uint32_t GetHeight() const {return mData.Height;}

        void ToggleCursor(bool toggle) const;

        void SetEventCallback(const EventCallbackFn &callback) {
            mData.EventCallback = callback;
        }


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
