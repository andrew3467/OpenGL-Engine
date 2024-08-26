//
// Created by Andrew Graser on 7/29/2024.
//

#ifndef OPENGL_ENGINE_RENDERER_H
#define OPENGL_ENGINE_RENDERER_H

namespace GLE {
    class Renderer {
    public:
        static void Init();

        static void SetClearColor(float r, float g, float b, float a = 1.0f);
        static void Clear();

    private:
        static bool sInitialized;
    };
}

#endif //OPENGL_ENGINE_RENDERER_H
