//
// Created by Andrew Graser on 7/31/2024.
//

#ifdef GLE_PLATFORM_WINDOWS

//Win32 Lib
#include <Windows.h>



#include "Core/Window.h"
#include "Core/Application.h"
#include "Glad/glad_wgl.h"

namespace GLE {
    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        switch (msg) {
            case WM_DESTROY: {
                auto window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
                break;
            }

            case WM_CLOSE: {
                PostQuitMessage(0);
                break;
            }

            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        return NULL;
    }

    bool InitOpenGL() {

    }

    std::shared_ptr<Window> Window::Create(const Window::WindowProps& props) {
        return std::make_shared<Window>(props);
    }

    Window::~Window() {
        auto windowHandle = (HWND)mWindowContainer.nativeWindow;

        wglDeleteContext((HGLRC)mWindowContainer.context);
        DestroyWindow(windowHandle);
    }

    Window::Window(const Window::WindowProps &props) {
        mData.Width = props.Width;
        mData.Height = props.Height;
        mData.Title = props.Title;

        WNDCLASSEX wc = {};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.lpszClassName = props.Title.c_str();
        wc.lpfnWndProc = &WndProc;

        auto classID = RegisterClassEx(&wc);
        GLE_ASSERT(classID, "Failed to register ClassX");

        RECT rc = {0, 0, (LONG)props.Width, (LONG)props.Height};
        AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);


        auto windowHandle = CreateWindowEx(
                NULL,
                MAKEINTATOM(classID),
                "OpenGL Engine",
                WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                rc.right - rc.left,
                rc.bottom - rc.top,
                NULL,
                NULL,
                NULL,
                NULL
        );

        GLE_ASSERT(windowHandle, "Failed to create Win32 Window");

        SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR)this);

        ShowWindow(windowHandle, SW_SHOW);
        UpdateWindow(windowHandle);

        //Creating OpenGL Render Context
        auto hDC = GetDC(windowHandle);

        int pixelFormatAttrib[] = {
                WGL_DRAW_TO_WINDOW_ARB,GL_TRUE,
                WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
                WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
                WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
                WGL_COLOR_BITS_ARB, 32,
                WGL_DEPTH_BITS_ARB, 24,
                WGL_STENCIL_BITS_ARB, 8,
                0
        };

        int pixelFormat = 0;
        UINT numFormats = 0;
        wglChoosePixelFormatARB(hDC, pixelFormatAttrib, nullptr, 1, &pixelFormat, &numFormats);

        GLE_ASSERT(numFormats, "OpenGL Context must have at least 1 format");

        PIXELFORMATDESCRIPTOR pixelFormatDesc = {};

        DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDesc);
        SetPixelFormat(hDC, pixelFormat, &pixelFormatDesc);

        int openGLAttributes[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
                WGL_CONTEXT_MINOR_VERSION_ARB, 6,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0
        };

        mWindowContainer.context = wglCreateContextAttribsARB(hDC, 0, openGLAttributes);




        mWindowContainer.nativeWindow = windowHandle;
    }

    void Window::SetupCallbacks() {

    }

    void Window::Update() {
        MSG msg = {};

        if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {

            if(msg.message == WM_QUIT) {
                Application::Get().Stop();
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        Sleep(1);

        wglMakeCurrent(GetDC((HWND)mWindowContainer.nativeWindow), HGLRC(mWindowContainer.context));
        wglSwapIntervalEXT(mData.VSYNC);
        wglSwapLayerBuffers(GetDC((HWND)mWindowContainer.nativeWindow), WGL_SWAP_MAIN_PLANE);
    }
}

#endif
