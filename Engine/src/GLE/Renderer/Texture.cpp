//
// Created by Andrew Graser on 9/15/2024.
//


#include "Texture.h"

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace GLE {
    std::unordered_map<std::string, std::shared_ptr<Texture2D>> sTextures;

    void Texture2D::Init() {
        for(auto& file : fs::directory_iterator(ASSETS_FOLDER + "textures/")) {
            std::string path = file.path().string();

            auto baseFileName = path.substr(path.find_last_of("\\/") + 1);
            int const p = baseFileName.find_last_of('.');
            auto fileName = baseFileName.substr(0, p);

            auto texture = Texture2D::Create(path);
            sTextures.emplace(fileName, texture);
            GLE_INFO("Created texture: {0}, resolution: ({1}, {2})", fileName.c_str(), texture->GetWidth(), texture->GetHeight());
        }
    }

    std::shared_ptr<Texture2D> Texture2D::Get(const std::string &name) {
        return sTextures[name];
    }

    std::unordered_map<std::string, std::shared_ptr<Texture2D>> Texture2D::GetTextures() {
        return sTextures;
    }
}
