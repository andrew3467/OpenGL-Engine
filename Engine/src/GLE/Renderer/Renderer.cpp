//
// Created by Andrew Graser on 7/29/2024.
//

#include <variant>
#include "Renderer/Renderer.h"

#include "Framebuffer.h"
#include "Core/Scene/ECS/Component/TransformComponent.h"
#include "Renderer/PrimitiveType.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Camera.h"
#include "RenderCommand.h"


#include "GLFW/glfw3.h"
#include "Glad/glad.h"



#ifdef GLE_PLATFORM_WINDOWS
#include <Glad/glad_wgl.h>
#include <windows.h>
#endif


namespace GLE {
    using InstancedData = std::map<std::shared_ptr<VertexArray>, std::vector<glm::mat4>>;

    class Framebuffer;

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoord;
    };

    struct RendererData {
        glm::mat4 ViewProj;
        glm::vec3 ViewPos;

        std::vector<std::shared_ptr<VertexArray>> VAs;

        std::vector<glm::vec3> LightColors;
        std::vector<glm::vec3> LightPositions;

        std::map<Material, InstancedData> InstanceData;
    };

    RendererData sData = {};

    RendererStats  Renderer::mStats = {};

    Framebuffer *framebuffer;

    void InitData() {
        framebuffer = new Framebuffer(1280, 720);

        sData.VAs.resize(4);

        {
            GLuint indices[] = {
                    0, 3, 2,
                    2, 1, 0
            };

            Vertex vertices[] = {
                    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},  // A 0
                    {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},  // B 1
                    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},  // C 2
                    {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},  // D 3
            };

            auto VA = VertexArray::Create();

            auto VB = VertexBuffer::Create(&vertices[0].Position.x, sizeof(vertices) / sizeof(float));
            VB->SetLayout({
                                  {ShaderDataType::Float3, "aPosition"},
                                  {ShaderDataType::Float3, "aNormal"},
                                  {ShaderDataType::Float2, "aTexCoord"},

                          });
            VA->SetVertexBuffer(VB);

            auto IB = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
            VA->SetIndexBuffer(IB);

            sData.VAs[(int)PrimitiveType::Quad] = VA;
        }

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

            //Position, Normal, TexCoord
            Vertex vertices[] = {
                    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},  // A 0
                    {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},  // B 1
                    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},  // C 2
                    {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},  // D 3
                    {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},  // E 4
                    {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},   // F 5
                    {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},   // G 6
                    {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},   // H 7

                    {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},  // D 8
                    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},  // A 9
                    {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},  // E 10
                    {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},  // H 11
                    {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},   // B 12
                    {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},   // C 13
                    {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, { 1.0f, 1.0f }},   // G 14
                    {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},   // F 15

                    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},  // A 16
                    {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},   // B 17
                    {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},   // F 18
                    {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},  // E 19
                    {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},  // C 20
                    {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},  // D 21
                    {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},  // H 22
                    {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},  // G 23
            };

            auto VA = VertexArray::Create();

            auto VB = VertexBuffer::Create(&vertices[0].Position.x, sizeof(vertices) / sizeof(float));
            VB->SetLayout({
                                  {ShaderDataType::Float3, "aPosition"},
                                  {ShaderDataType::Float3, "aNormal"},
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
        sData.ViewPos = camera.GetPosition();

        mStats = {};
    }

    /// Note: All texture in shader programs must follow below bindings
    /// Albedo - 0
    /// Diffuse - 1
    /// Normal - 2
    /// Roughness - 3
    void Renderer::BindMaterial(const Material &material) {
        auto& shader = material.Shader;

        if(!shader) {
            GLE_ERROR("ERROR: Material passed to BindMaterial missing shader");
            return;
        }

        shader->Bind();

        shader->SetFloat3("uColor", material.Albedo);

        if(material.AlbedoMap != nullptr) {
            material.AlbedoMap->Bind(0);
        }

        if(material.DiffuseMap != nullptr) {
            material.DiffuseMap->Bind(1);
        }

        if(material.NormalMap != nullptr) {
            material.NormalMap->Bind(2);
        }
    }

    void Renderer::UnbindMaterial(const Material &material) {
        if(material.AlbedoMap != nullptr) {
            material.AlbedoMap->Unbind();
        }

        if(material.DiffuseMap != nullptr) {
            material.DiffuseMap->Unbind();
        }

        if(material.NormalMap != nullptr) {
            material.NormalMap->Unbind();
        }
    }

    void Renderer::BindLights(const std::vector<glm::vec3> &lights, Shader& shader, const std::vector<glm::vec3> &positions) {
        sData.LightColors = lights;
        sData.LightPositions = positions;
    }

    void Renderer::SubmitPrimitive(PrimitiveType primitive, Material& material, const glm::mat4& transform) {
         Submit(sData.VAs[(int)primitive], material, transform);
    }

    void Renderer::Submit(std::shared_ptr<VertexArray>& VA, Material &material, const glm::mat4 &transform) {
        auto shader = *material.Shader;
        shader.Bind();
#if 0
        shader.SetInt("uNumLights", sData.LightPositions.size());
        for(int i = 0; i < sData.LightPositions.size(); i++) {
            auto index = std::string("uPointLights[").append(std::to_string(i)).append("]");


            shader.SetFloat3((index + ".Position").c_str(), sData.LightPositions[i]);
            shader.SetFloat3((index + ".Color").c_str(), sData.LightColors[i]);
        }
#endif

        shader.SetFloat3("uViewPos", sData.ViewPos);

        shader.SetFloat4x4("uViewProj", sData.ViewProj);
        shader.SetFloat4x4("uModel", transform);

        //sData.InstanceData[material][VA].push_back(transform);

        RenderCommand::DrawIndexed(*VA);
    }

    void Renderer::RenderScene() {
    }
};
