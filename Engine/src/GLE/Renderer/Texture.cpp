//
// Created by Andrew Graser on 9/15/2024.
//


#include "Texture.h"

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace GLE {
    std::unordered_map<std::string, std::shared_ptr<Texture2D>> sTextures;

    void Texture2D::Init() { {
            GLE_INFO("Creating Default Texture");

            auto defTex = Create(1,1);
            uint32_t data = 0xffffffff;
            defTex->SetData(&data, sizeof(uint32_t));

            sTextures.emplace("Default", defTex);
        }
        for(auto& file : fs::directory_iterator(ASSETS_FOLDER + "textures/")) {
            std::string path = file.path().string();

            auto texture = Texture2D::Create(path);
            sTextures.emplace(texture->GetName(), texture);
            GLE_INFO("Created texture: {0}, resolution: ({1}, {2})", texture->GetName(), texture->GetWidth(), texture->GetHeight());
        }
    }

    std::shared_ptr<Texture2D> Texture2D::Get(const std::string &name) {
        return sTextures[name];
    }

    std::unordered_map<std::string, std::shared_ptr<Texture2D>> Texture2D::GetTextures() {
        return sTextures;
    }
}
