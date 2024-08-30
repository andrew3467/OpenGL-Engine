//
// Created by Andrew Graser on 7/29/2024.
//

#include "Renderer/Renderer.h"
#include "Renderer/PrimitiveType.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Camera.h"
#include "Core/Window.h"

#include "GLFW/glfw3.h"
#include "Glad/glad.h"
#include "glm/gtx/rotate_vector.hpp"


#ifdef GLE_PLATFORM_WINDOWS
#include <Glad/glad_wgl.h>
#include <windows.h>
#endif

namespace GLE {
    struct RendererData {
        glm::mat4 ViewProj;

        std::vector<std::shared_ptr<VertexArray>> VAs;
    };

    RendererData sData = {};

    void InitData() {
        sData.VAs.resize(2);

        {
            uint32_t indices[] = {
                    0, 1, 5,  5, 1, 6,
                    1, 2, 6,  6, 2, 7,
                    2, 3, 7,  7, 3, 8,
                    3, 4, 8,  8, 4, 9,
                    10,11, 0,  0,11, 1,
                    5, 6,12, 12, 6,13
            };

            //Position, TexCoord
             float vertices[] = {
                     -1,-1,-1, 0, 0,
                    1,-1,-1, 1, 0,
                    1, 1,-1, 2, 0,
                    -1, 1,-1, 3, 0,
                    -1,-1,-1, 4, 0,

                    -1,-1, 1, 0, 1,
                    1,-1, 1, 1, 1,
                    1, 1, 1, 2, 1,
                    -1, 1, 1, 3, 1,
                    -1,-1, 1, 4, 1,

                    -1, 1,-1, 0,-1,
                    1, 1,-1, 1,-1,

                    -1, 1, 1, 0, 2,
                    1, 1, 1, 1, 2
            };

            auto VA = VertexArray::Create();

            auto VB = VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
            VB->SetLayout({
                                  {3, GL_FLOAT, 0, false},
                                  {2, GL_FLOAT, 3, false},

                          });
            VA->SetVertexBuffer(VB);

            auto IB = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
            VA->SetIndexBuffer(IB);

            sData.VAs[(int)PrimitiveType::Cube] = VA;
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

    void Renderer::StartScene(PerspectiveCamera& camera) {
        //ViewProj == Proj * View
        sData.ViewProj = camera.GetViewProjection();
    }

    void Renderer::RenderScene() {

    }

    void Renderer::SubmitPrimitive(PrimitiveType primitive, Shader& shader) {
        const auto& VA = sData.VAs[(int)primitive];

        VA->Bind();

        shader.SetFloat3("uColor", {1,0,1});

        shader.Bind();
        shader.SetFloat4x4("uViewProj", sData.ViewProj);
        shader.SetFloat4x4("uModel", glm::mat4(1));
        glDrawElements(GL_TRIANGLES, VA->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}