//
// Created by Andrew Graser on 7/28/2024.
//


#ifdef GLE_PLATFORM_GLFW


#include "GLFW/glfw3.h"

#include "Core/Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"

namespace GLE {
    static void GLFWErrorCallback(int error_code, const char* description){
        std::cerr << "GLFW Error: (" << error_code << ")" << description << "\n";
    }

    static void InitGLFW() {
        static bool glfwInitialized = false;
        if(glfwInitialized) return;

        glfwSetErrorCallback(GLFWErrorCallback);

        if(!glfwInit()){
            GLE_ERROR("Error: Failed to initialize GLFW!");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        glfwInitialized = true;
    }

    Window::~Window() {
        glfwDestroyWindow((GLFWwindow*)mWindowContainer.nativeWindow);
        glfwTerminate();
    }


    std::shared_ptr<Window> Window::Create(const Window::WindowProps& props) {
        return std::make_shared<Window>(props);
    }

    Window::Window(const Window::WindowProps &props) {
        mData.Width = props.Width;
        mData.Height = props.Height;
        mData.Title = props.Title;

        mWindowContainer = {};

        InitGLFW();

        GLFWwindow* window = glfwCreateWindow(mData.Width, mData.Height, mData.Title.c_str(), nullptr, nullptr);

        GLE_ASSERT(window != nullptr, "Error: Failed to create GLFW window!");
        GLE_INFO("Created GLFW window of size: ({0}, {1})", mData.Width, mData.Height);

        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, &mData);

        mWindowContainer.nativeWindow = window;

        SetupCallbacks();
    }

#include "Events/MouseEvent.h"
    void Window::SetupCallbacks() {
        glfwSetWindowCloseCallback((GLFWwindow*)GetNativeWindow(), [](GLFWwindow* window) {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetWindowSizeCallback((GLFWwindow*)GetNativeWindow(), [](GLFWwindow* window, int width, int height) {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetKeyCallback((GLFWwindow*)GetNativeWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });
    }

    void Window::Update() {
        glfwSwapBuffers((GLFWwindow*)GetNativeWindow());
        glfwPollEvents();
    }
}

#endif