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


        [[nodiscard]] uint32_t GetWidth() const {return mWidth;}
        [[nodiscard]] uint32_t GetHeight() const {return mHeight;}
        [[nodiscard]] const std::string& GetName() const {return mName;}


    protected:
        uint32_t LoadTextureData(const std::string& path);



    protected:
        unsigned char* mData;
        std::string mFileLoc;
        uint32_t mRendererID;

        int mWidth, mHeight, mChannels;

        std::string mName;
    };

    class Texture2D : public Texture {
    public:
        static std::shared_ptr<Texture2D> Create(const std::string& path) {return std::make_shared<Texture2D>(path);}
        static void Init();
        static std::shared_ptr<Texture2D> Get(const std::string& name);
        static std::unordered_map<std::string, std::shared_ptr<Texture2D>> GetTextures();

    public:
        Texture2D(const std::string& path);
        ~Texture2D();
    };
}
