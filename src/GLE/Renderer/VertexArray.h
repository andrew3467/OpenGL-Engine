//
// Created by Andrew Graser on 8/26/2024.
//

#ifndef OPENGL_ENGINE_VERTEXARRAY_H
#define OPENGL_ENGINE_VERTEXARRAY_H

#include "Buffer.h"

namespace GLE {
    class VertexArray {
    public:
        inline static std::shared_ptr<VertexArray> Create() {return std::make_shared<VertexArray>();}


    public:
        VertexArray();
        ~VertexArray() = default;

        void Bind();
        void Unbind();

        inline VertexBuffer& GetVertexBuffer() { return *mVertexBuffer;}
        inline IndexBuffer& GetIndexBuffer() { return *mIndexBuffer;}

        void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer);
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer);

    private:
        uint32_t mRendererID;

        std::shared_ptr<VertexBuffer> mVertexBuffer;
        std::shared_ptr<IndexBuffer> mIndexBuffer;
    };
}

#endif //OPENGL_ENGINE_VERTEXARRAY_H
