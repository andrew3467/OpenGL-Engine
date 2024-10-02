//
// Created by apgra on 9/4/2024.
//

#ifndef OPENGL_ENGINE_RENDERCOMMAND_H
#define OPENGL_ENGINE_RENDERCOMMAND_H

#include "VertexArray.h"

namespace GLE {
    namespace RenderCommand {
        void SetClearColor(float r, float g, float b);
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

        void DrawIndexed(VertexArray &VA);

        void ClearBuffers();

        void DrawIndexedInstanced(VertexArray &VA, uint32_t instanceCount);

        void ToggleWireframe(bool toggle);
    }
}

#endif //OPENGL_ENGINE_RENDERCOMMAND_H
