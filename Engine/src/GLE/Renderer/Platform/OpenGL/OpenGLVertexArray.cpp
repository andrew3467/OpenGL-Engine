//
// Created by Andrew Graser on 8/26/2024.
//

#ifdef GLE_PLATFORM_GLFW

#include "Renderer/VertexArray.h"

#include <Glad/glad.h>

namespace GLE {
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:    return GL_FLOAT;
            case ShaderDataType::Float2:   return GL_FLOAT;
            case ShaderDataType::Float3:   return GL_FLOAT;
            case ShaderDataType::Float4:   return GL_FLOAT;
            case ShaderDataType::Mat3:     return GL_FLOAT;
            case ShaderDataType::Mat4:     return GL_FLOAT;
            case ShaderDataType::Int:      return GL_INT;
            case ShaderDataType::Int2:     return GL_INT;
            case ShaderDataType::Int3:     return GL_INT;
            case ShaderDataType::Int4:     return GL_INT;
            case ShaderDataType::Bool:     return GL_BOOL;
        }

        GLE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    VertexArray::VertexArray() {
        glGenVertexArrays(1, &mRendererID);
        glBindVertexArray(mRendererID);
    }

    void VertexArray::Bind() {
        glBindVertexArray(mRendererID);
    }

    void VertexArray::Unbind() {
        glBindVertexArray(0);
    }

    void VertexArray::SetVertexBuffer(const std::shared_ptr<VertexBuffer> &buffer) {
        mVertexBuffer = buffer;

        glBindVertexArray(mRendererID);
        buffer->Bind();


        int index = 0;
        const auto& layout = buffer->GetLayout();
        for(const auto& element : layout) {
            switch (element.Type)
            {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                {
                    glEnableVertexAttribArray(mVertexBufferIndex);
                    glVertexAttribPointer(mVertexBufferIndex,
                        element.GetComponentCount(),
                        ShaderDataTypeToOpenGLBaseType(element.Type),
                        element.Normalized ? GL_TRUE : GL_FALSE,
                        layout.GetStride(),
                        (const void*)element.Offset);
                    mVertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool:
                {
                    glEnableVertexAttribArray(mVertexBufferIndex);
                    glVertexAttribIPointer(mVertexBufferIndex,
                        element.GetComponentCount(),
                        ShaderDataTypeToOpenGLBaseType(element.Type),
                        layout.GetStride(),
                        (const void*)element.Offset);
                    mVertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4:
                {
                    uint8_t count = element.GetComponentCount();
                    for (uint8_t i = 0; i < count; i++)
                    {
                        glEnableVertexAttribArray(mVertexBufferIndex);
                        glVertexAttribPointer(mVertexBufferIndex,
                            count,
                            ShaderDataTypeToOpenGLBaseType(element.Type),
                            element.Normalized ? GL_TRUE : GL_FALSE,
                            layout.GetStride(),
                            (const void*)(element.Offset + sizeof(float) * count * i));
                        glVertexAttribDivisor(mVertexBufferIndex, 1);
                        mVertexBufferIndex++;
                    }
                    break;
                }
                default:
                    GLE_ASSERT(false, "Unknown ShaderDataType!");
            }
        }
    }

    void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &buffer) {
        mIndexBuffer = buffer;

        glBindVertexArray(mRendererID);
        buffer->Bind();
    }
}

#endif