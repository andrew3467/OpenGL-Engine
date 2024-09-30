//
// Created by Andrew Graser on 9/29/2024.
//

#ifdef GLE_PLATFORM_GLFW

#include "Renderer/Framebuffer.h"

#include <glad/glad.h>

namespace GLE {
    Framebuffer::Framebuffer(int width, int height) {
        mOutputTexture = Texture2D::Create(width, height, "Framebuffer output");

        glGenFramebuffers(1, &mRendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, mRendererID);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mOutputTexture->GetID(), 0);

        GLE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

    Framebuffer::Framebuffer(const Framebuffer &other) {
    }

    Framebuffer::~Framebuffer() {
        glDeleteFramebuffers(1, &mRendererID);
    }

    void Framebuffer::Bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, mRendererID);
    }

    void Framebuffer::Unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

#endif
