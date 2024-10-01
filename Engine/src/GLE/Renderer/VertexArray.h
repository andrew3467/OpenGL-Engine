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

        std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() { return mVertexBuffers;}
        IndexBuffer& GetIndexBuffer() { return *mIndexBuffer;}

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer> & vb);
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer);



    private:
        uint32_t mRendererID;
        uint32_t mVertexBufferIndex = 0;

        std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
        std::shared_ptr<IndexBuffer> mIndexBuffer;
    };
}

#endif //OPENGL_ENGINE_VERTEXARRAY_H
