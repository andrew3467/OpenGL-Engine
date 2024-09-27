//
// Created by Andrew Graser on 9/7/2024.
//


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <Glad/glad.h>

#include "Renderer/Texture.h"


void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        GLE_ASSERT(false, "GL ERROR")
        GLE_ERROR("OpenGL error {0}, at {1}:{2} - for {3}\n", err, fname, line, stmt);
    }
}

#ifdef _DEBUG
    #define GL_CHECK(stmt) do { \
    stmt; \
    CheckOpenGLError(#stmt, __FILE__, __LINE__); \
    } while (0)
#else
    #define GL_CHECK(stmt) stmt
#endif

namespace GLE {


    uint32_t Texture::LoadTextureData(const std::string& path) {
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(path.c_str(), &mWidth, &mHeight, &mChannels, 0);


        if(!data) {
            GLE_ERROR("Failed to load texture at {0}", path);
        }


        switch (mChannels) {
            case 1:
                mDataFormat = GL_R;
                mInternalFormat = GL_R8;
                break; //STBI_grey
            case 2:
                mDataFormat = GL_RG;
                mInternalFormat = GL_RG8;
                break; //STBI_grey_alpha
            case 3:
                mDataFormat = GL_RGB;
                mInternalFormat = GL_RGB8;
                break; //STBI_rgb

            case 4:
                mDataFormat = GL_RGBA;
                mInternalFormat = GL_RGBA8;
                break; //STBI_rgb_alpha
        }

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexStorage2D(GL_TEXTURE_2D, 1, mInternalFormat, mWidth, mHeight);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        glTexSubImage2D(
            mRendererID,
            0,
            0,
            0,
            mWidth,
            mHeight,
            mDataFormat,
            GL_UNSIGNED_BYTE,
            data
        );

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);

        auto baseFileName = path.substr(path.find_last_of("\\/") + 1);
        int const p = baseFileName.find_last_of('.');
        mName = baseFileName.substr(0, p);

        return textureID;
    }


#pragma region Texture2D


    Texture2D::Texture2D(int width, int height)
    {
        mWidth = width;
        mHeight = height;
        mChannels = 4;

        mInternalFormat = GL_RGBA;
        mDataFormat = GL_RGBA;

        glGenTextures(1, &mRendererID);
        glBindTexture(GL_TEXTURE_2D, mRendererID);

        glTexStorage2D(GL_TEXTURE_2D, 1, mInternalFormat, mWidth, mHeight);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Texture2D::Texture2D(const std::string &path) {
        mFileLoc = path;
        mRendererID = LoadTextureData(path);
    }

    Texture2D::~Texture2D() {
        glDeleteTextures(1, &mRendererID);
    }

    void Texture2D::SetData(void *data, uint32_t size) {
        uint32_t bpp = mDataFormat == GL_RGB ? 3 : 4;
        GLE_ASSERT(size == mWidth * mHeight * bpp, "Data must consist of entire texture!");

        glTexSubImage2D(
            mRendererID,
            0,
            0,
            0,
            mWidth,
            mHeight,
            mDataFormat,
            GL_UNSIGNED_BYTE,
            data
            );
    }

    void Texture::Bind(int loc) const {
        GLE_ASSERT(loc < 31, std::string("Only 32 texture slots are supported, given slot: ") + std::to_string(loc));

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
