//
// Created by Andrew Graser on 9/29/2024.
//


#pragma once
#include "Texture.h"

namespace GLE {
    class Framebuffer {
    public:
        static std::shared_ptr<Framebuffer> Create(int width, int height) {return std::make_shared<Framebuffer>(width, height);}

    public:
        Framebuffer(int width, int height);
        Framebuffer(const Framebuffer& other);
        ~Framebuffer();

        void Bind() const;
        void Unbind() const;

    private:
        uint32_t mRendererID = 0;
        uint32_t mWidth = 0, mHeight = 0;

        std::shared_ptr<Texture2D> mOutputTexture;
    };
}
