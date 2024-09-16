//
// Created by Andrew Graser on 7/29/2024.
//

#include "Renderer/Renderer.h"

#include "Core/Scene/ECS/Component/TransformComponent.h"
#include "Renderer/PrimitiveType.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Camera.h"
#include "Core/Window.h"

#include "GLFW/glfw3.h"
#include "Glad/glad.h"
#include "glm/detail/type_quat.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "RenderCommand.h"
#include "Texture.h"


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

    RendererStats  Renderer::mStats = {};

    void InitData() {
        sData.VAs.resize(2);

        {
            GLuint indices[] = {
                // front and back
                0, 3, 2,
                2, 1, 0,
                4, 5, 6,
                6, 7 ,4,
                // left and right
                11, 8, 9,
                9, 10, 11,
                12, 13, 14,
                14, 15, 12,
                // bottom and top
                16, 17, 18,
                18, 19, 16,
                20, 21, 22,
                22, 23, 20
            };

            //Position, TexCoord
            GLfloat vertices[] = {
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 0
                0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // B 1
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // C 2
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // D 3
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // E 4
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   // F 5
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 6
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   // H 7

                -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // D 8
                -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // A 9
                -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // E 10
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // H 11
                0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // B 12
                0.5f,  0.5f, -0.5f,  1.0f, 0.0f,   // C 13
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 14
                0.5f, -0.5f,  0.5f,  0.0f, 1.0f,   // F 15

                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 16
                0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   // B 17
                0.5f, -0.5f,  0.5f,  1.0f, 1.0f,   // F 18
                -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // E 19
                0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // C 20
                -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  // D 21
                -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // H 22
                0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  // G 23
            };

            auto VA = VertexArray::Create();

            auto VB = VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
            VB->SetLayout({
                                  {ShaderDataType::Float3, "aPosition"},
                                  {ShaderDataType::Float2, "aTexCoord"},

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

        glEnable(GL_DEPTH_TEST);
#endif

        InitData();
        sInitialized = true;
    }

    void Renderer::SetClearColor(float r, float g, float b) {
        RenderCommand::SetClearColor(r,g,b);
    }

    void Renderer::UpdateViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        RenderCommand::SetViewport(x, y, width, height);
    }

    void Renderer::Clear() {
        RenderCommand::ClearBuffers();
    }


    void Renderer::StartScene(Camera& camera) {
        //ViewProj == Proj * View
        sData.ViewProj = camera.GetViewProjection();

        mStats = {};
    }

    void Renderer::RenderScene() {

    }

    /// Note: All texture in shader programs must follow below bindings
    /// Albedo - 0
    /// Diffuse - 1
    /// Normal - 2
    /// Roughness - 3
    void Renderer::BindMaterial(const Material &material) {
        auto& shader = material.Shader;

        if(shader == nullptr) {
            GLE_ERROR("ERROR: Material passed to material missing shader");
            return;
        }

        shader->Bind();

        shader->SetFloat3("uColor", material.Albedo);

        if(material.AlbedoMap != nullptr) {
            material.AlbedoMap->Bind(0);
            shader->SetInt("uAlbedoMap", 0);
        }

        if(material.DiffuseMap != nullptr) {
            material.DiffuseMap->Bind(1);
            shader->SetInt("uDiffuseMap", 1);
        }

        if(material.NormalMap != nullptr) {
            material.NormalMap->Bind(2);
            shader->SetInt("uNormalMap", 2);
        }
    }

    void Renderer::SubmitPrimitive(PrimitiveType primitive, Shader& shader, const glm::mat4& transform) {
         Submit(*sData.VAs[(int)primitive], shader, transform);
    }

    void Renderer::Submit(VertexArray &VA, Shader &shader, const glm::mat4 &transform) {
        shader.Bind();

        shader.SetFloat3("uColor", {1,0,1});

        shader.SetFloat4x4("uViewProj", sData.ViewProj);
        shader.SetFloat4x4("uModel", transform);

        mStats.NumDrawCalls++;
        RenderCommand::DrawIndexed(VA);
    }
}
