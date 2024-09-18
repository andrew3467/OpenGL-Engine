//
// Created by Andrew Graser on 9/7/2024.
//


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <Glad/glad.h>

#include "Renderer/Texture.h"


namespace GLE {
    uint32_t Texture::LoadTextureData(const std::string& path) {
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(path.c_str(), &mWidth, &mHeight, &mChannels, 0);


        if(!data) {
            GLE_ERROR("Failed to load texture at {0}", path);
        }

        GLenum format;
        switch (mChannels) {
            case 1: format = GL_RED;  break; //STBI_grey
            case 2: format = GL_RG;   break; //STBI_grey_alpha
            case 3: format = GL_RGB;  break; //STBI_rgb
            case 4: format = GL_RGBA; break; //STBI_rgb_alpha
        }

        GLuint textureID;

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,                      //Mipmap level - 0
            format,
            mWidth,
            mHeight,
            0,
            format,
            GL_UNSIGNED_BYTE,
            data
            );

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);

        auto baseFileName = path.substr(path.find_last_of("\\/") + 1);
        int const p = baseFileName.find_last_of('.');
        mName = baseFileName.substr(0, p);

        return textureID;
    }


#pragma region Texture2D

    Texture2D::Texture2D(const std::string &path) {
        mFileLoc = path;
        mRendererID = LoadTextureData(path);
    }

    Texture2D::~Texture2D() {
        glDeleteTextures(1, &mRendererID);
    }

    void Texture::Bind(int loc) const {
        GLE_ASSERT(loc < 31, "Cannot bind texture at location > 32");

        glActiveTexture(GL_TEXTURE0 + loc);
        glBindTexture(GL_TEXTURE_2D, mRendererID);
    }

    void Texture::Unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }


#pragma endregion
#pragma region Texture3D


#pragma endregion


}
