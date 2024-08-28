//
// Created by Andrew Graser on 7/29/2024.
//

#include "Renderer/Renderer.h"
#include "Renderer/PrimitiveType.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Core/Window.h"

#include "GLFW/glfw3.h"
#include "Glad/glad.h"


#ifdef GLE_PLATFORM_WINDOWS
#include <Glad/glad_wgl.h>
#include <windows.h>
#endif

namespace GLE {
    struct RendererData {
        std::shared_ptr<Shader> StandardShader;

        std::vector<std::shared_ptr<VertexArray>> VAs;
    };

    RendererData sData = {};

    void InitData() {
        sData.StandardShader = Shader::Create("../assets/shaders/Standard.glsl");

        sData.VAs.resize(2);

        {
            float vertices[] = {
                    -0.5f, -0.5f, 0.0f,
                    -0.5f, 0.5f, 0.0f,
                    0.5f, -0.5f, 0.0f,
                    0.5f, 0.5f, 0.0f
            };

            uint32_t indices[] = {
                    0, 1, 2,
                    2, 3, 1
            };

            auto VA = VertexArray::Create();

            auto VB = VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
            VB->SetLayout({
                                  {3, GL_FLOAT, 0, false},

                          });
            VA->SetVertexBuffer(VB);

            auto IB = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
            VA->SetIndexBuffer(IB);

            sData.VAs[0] = VA;
        }
    }

    bool Renderer::sInitialized = false;

    void Renderer::Init() {
        if(sInitialized) {
            GLE_WARN("WARNING: Renderer::Init called multiple times");
            return;
        }

#ifdef GLE_PLATFORM_WINDOWS
        WNDCLASSEX wc = {};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.lpszClassName = "OGLDummyWindow";
        wc.lpfnWndProc = DefWindowProc;
        wc.style = CS_OWNDC;

        auto classID = RegisterClassEx(&wc);
        GLE_ASSERT(classID, "Failed to register ClassX");


        auto dummyWindowHandle = CreateWindowEx(
                NULL,
                MAKEINTATOM(classID),
                "OpenGL Engine",
                WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                NULL,
                NULL,
                NULL,
                NULL
        );

        GLE_ASSERT(dummyWindowHandle, "Failed to create Win32 Rendering Window");

        auto dummyDC = GetDC(dummyWindowHandle);
        PIXELFORMATDESCRIPTOR pixelformatdescriptor {};
        pixelformatdescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pixelformatdescriptor.nVersion = 1;
        pixelformatdescriptor.iPixelType = PFD_TYPE_RGBA;
        pixelformatdescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pixelformatdescriptor.cColorBits = 32;
        pixelformatdescriptor.cAlphaBits = 8;
        pixelformatdescriptor.cDepthBits = 24;
        pixelformatdescriptor.cStencilBits = 8;
        pixelformatdescriptor.iLayerType = PFD_MAIN_PLANE;

        auto pixelFormat = ChoosePixelFormat(dummyDC, &pixelformatdescriptor);
        SetPixelFormat(dummyDC, pixelFormat, &pixelformatdescriptor);

        //OpenGL entry point
        auto dummyContext = wglCreateContext(dummyDC);
        GLE_ASSERT(dummyContext, "Failed to create OpenGL Context");

        wglMakeCurrent(dummyDC, dummyContext);

        if(!gladLoadWGLLoader((GLADloadproc) wglGetProcAddress, dummyDC)) {
            throw std::runtime_error("GLE - Error: gladLoadWGL Failed");
        }

        if(!gladLoadGL()) {
            throw std::runtime_error("GLE - Error: gladLoadGL Failed");
        }

        wglMakeCurrent(dummyDC, 0);
        wglDeleteContext(dummyContext);
        ReleaseDC(dummyWindowHandle, dummyDC);
        DestroyWindow(dummyWindowHandle);

        GLE_INFO("Created OpenGL rendering context for Win32 Window");

#endif

#ifdef GLE_PLATFORM_GLFW
        int success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        GLE_ASSERT(success, "ERROR: Failed to initialize GLAD!");
#endif

        InitData();
        sInitialized = true;
    }

    void Renderer::SetClearColor(float r, float g, float b, float a) {
        glClearColor(r,g,b,a);
    }

    void Renderer::UpdateViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(x, y, width, height);
    }

    void Renderer::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::StartScene() {
        sData.StandardShader->Bind();
        sData.StandardShader->SetFloat3("uColor", {1.0f, 0.0f, 1.0f});


        //glm::ivec4 viewport;
        //glGetIntegerv(GL_VIEWPORT, &viewport.x);
        //ViewProj == Proj * View
        sData.StandardShader->SetFloat4x4("uViewProj", glm::mat4(1));
    }

    void Renderer::RenderScene() {

    }

    void Renderer::SubmitPrimitive(PrimitiveType primitive) {
        auto& VA = sData.VAs[(int)primitive];

        VA->Bind();
        sData.StandardShader->Bind();
        sData.StandardShader->SetFloat4x4("uModel", glm::mat4(1));
        glDrawElements(GL_TRIANGLES, VA->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, 0);
    }
}