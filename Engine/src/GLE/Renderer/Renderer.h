//
// Created by Andrew Graser on 7/29/2024.
//

#ifndef OPENGL_ENGINE_RENDERER_H
#define OPENGL_ENGINE_RENDERER_H

#include "Material.h"
#include "PrimitiveType.h"
#include "VertexArray.h"
#include "glm/fwd.hpp"


namespace GLE {
    class Camera;
    class Shader;

    struct TransformComponent;

    struct RendererStats {
        uint32_t NumDrawCalls;
    };


    class Renderer {
    public:
        static RendererStats GetStats() { return mStats; }

        static void Init();

        static void UpdateViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        static void SetClearColor(float r, float g, float b);
        static void Clear();

        static void StartScene(Camera& camera);
        static void RenderScene();

        static void BindMaterial(const Material &material);

        static void SubmitPrimitive(PrimitiveType primitive, Shader& shader, const glm::mat4& transform);
        static void Submit(VertexArray& VA, Shader& shader, const glm::mat4& transform);

    private:
        static bool sInitialized;
        static RendererStats mStats;
    };
}

#endif //OPENGL_ENGINE_RENDERER_H
