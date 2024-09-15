//
// Created by Andrew Graser on 9/7/2024.
//


#pragma once


namespace GLE {
    class Texture {
    public:
        Texture() {}
        virtual ~Texture() {}


        void Bind(int loc = 0) const;
        void Unbind() const;


    protected:
        uint32_t LoadTextureData(const std::string& path);



    protected:
        unsigned char* mData;
        std::string mFileLoc;
        uint32_t mRendererID;

        int mWidth, mHeight, mChannels;
    };

    class Texture2D :public Texture {
    public:
        static std::shared_ptr<Texture2D> Create(const std::string& path) {return std::make_shared<Texture2D>(ASSETS_FOLDER + path);}

    public:
        Texture2D(const std::string& path);
        ~Texture2D();
    };
}
