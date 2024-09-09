//
// Created by Andrew Graser on 9/7/2024.
//


#include <Glad/glad.h>
#include "SOIL2/SOIL2.h"

#include "Renderer/Texture.h"


namespace GLE {
    uint32_t Texture::LoadTextureData(const std::string& path) {
        uint32_t tex2D = SOIL_load_OGL_texture(
            path.c_str(),
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_TEXTURE_REPEATS
            );

        GLE_ASSERT(tex2D, "Failed to load texture at {0}", path);

        return tex2D;
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
