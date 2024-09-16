//
// Created by Andrew Graser on 9/15/2024.
//


#include "Texture.h"

namespace GLE {
    std::unordered_map<std::string, std::shared_ptr<Texture2D>> sTextures;

    void Texture2D::Init() {
        sTextures.emplace("Bricks", Texture2D::Create("textures/bricks.jpg"));
    }

    std::shared_ptr<Texture2D> Texture2D::Get(const std::string &name) {
        return sTextures[name];
    }
}