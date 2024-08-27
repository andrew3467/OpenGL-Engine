//
// Created by Andrew Graser on 8/26/2024.
//

#ifndef OPENGL_ENGINE_BUFFER_H
#define OPENGL_ENGINE_BUFFER_H

namespace GLE {
    class VertexBuffer {
    public:
        struct LayoutElement {
            uint32_t Size;      //Num of values
            uint32_t Type;
            uint32_t Offset;

            bool Normalized;
        };

        struct VertexBufferLayout {
            VertexBufferLayout() = default;
            VertexBufferLayout(const std::initializer_list<LayoutElement> elements) : Elements(elements), Stride(0) {
                for(auto& elem : elements) {
                    //TODO: Create Dedicated function when abstracting platform API
                    Stride += elem.Size * sizeof(float);
                }
            }

            uint32_t Stride;
            std::vector<LayoutElement> Elements;
        };


    public:
        inline static std::shared_ptr<VertexBuffer> Create(float* data, uint32_t count) {return std::make_shared<VertexBuffer>(data, count);}

        VertexBuffer(float* data, uint32_t count);
        ~VertexBuffer();

        void SetLayout(const VertexBufferLayout& layout) {mLayout = layout;}
        const VertexBufferLayout& GetLayout() const {return mLayout;}

        void Bind() const;
        void Unbind() const;


    private:
        uint32_t mRendererID;

        float* mData;
        uint32_t mCount;
        VertexBufferLayout mLayout;
    };

    class IndexBuffer {
    public:
        inline static std::shared_ptr<IndexBuffer> Create(uint32_t* data, uint32_t count) {return std::make_shared<IndexBuffer>(data, count);}

        IndexBuffer(uint32_t* data, uint32_t count);
        ~IndexBuffer();

        inline uint32_t GetCount() const {return mCount;}

        void Bind() const;
        void Unbind() const;


    private:
        uint32_t mRendererID;

        uint32_t* mData;
        uint32_t mCount;
    };
}

#endif //OPENGL_ENGINE_BUFFER_H
