//
// Created by Andrew Graser on 7/29/2024.
//

#ifndef OPENGL_ENGINE_RENDERER_H
#define OPENGL_ENGINE_RENDERER_H

#include "PrimitiveType.h"


namespace GLE {
    class Camera;
    class Shader;

    struct TransformComponent;


    class Renderer {
    public:
        static void Init();

        static void UpdateViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        static void SetClearColor(float r, float g, float b, float a = 1.0f);
        static void Clear();

        static void StartScene(Camera& camera);
        static void RenderScene();

        static void SubmitPrimitive(PrimitiveType primitive, Shader& shader, const TransformComponent& transform);

    private:
        static bool sInitialized;
    };
}

#endif //OPENGL_ENGINE_RENDERER_H
