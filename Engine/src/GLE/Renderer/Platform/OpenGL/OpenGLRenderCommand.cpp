//
// Created by apgra on 9/4/2024.
//


#ifdef GLE_PLATFORM_OPENGL

#include "Renderer/RenderCommand.h"

#include <glad/glad.h>

namespace GLE {
    void RenderCommand::SetClearColor(float r, float g, float b) {
        glClearColor(r,g,b,1);
    }

    void RenderCommand::ClearBuffers() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderCommand::DrawIndexedInstanced(VertexArray &VA, uint32_t instanceCount) {
        glDrawElementsInstanced(GL_TRIANGLES, VA.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr, instanceCount);
    }

    void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(x, y, width, height);
    }

    void RenderCommand::DrawIndexed(VertexArray &VA) {
        VA.Bind();
        glDrawElements(GL_TRIANGLES, VA.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void RenderCommand::ToggleWireframe(bool toggle)
    {
        glPolygonMode(GL_FRONT_AND_BACK, toggle ? GL_FILL : GL_LINE);
    }
}

#endif