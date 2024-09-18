//
// Created by Andrew Graser on 9/13/2024.
//


#include "Shader.h"


namespace GLE {
    std::unordered_map<std::string, std::shared_ptr<Shader>> Shader::mShaders;

    void Shader::Init() {
        mShaders.emplace("Standard", Shader::Create(ASSETS_FOLDER + "shaders/Standard.glsl"));
    }

}