//
// Created by Andrew Graser on 9/13/2024.
//


#include "Shader.h"


#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace GLE {
    std::unordered_map<std::string, std::shared_ptr<Shader>> sShaders;

    void Shader::Init() {
        for(auto& file : fs::directory_iterator(ASSETS_FOLDER + "shaders/")) {
            std::string path = file.path().string();

            auto shader = Shader::Create(path);
            sShaders.emplace(shader->GetName(), shader);
            GLE_INFO("Created shader: {0}", shader->GetName());
        }
    }

    std::shared_ptr<Shader> Shader::Get(const std::string &name) {
        return sShaders[name];
    }

    std::unordered_map<std::string, std::shared_ptr<Shader>> Shader::GetShaders() {
        return sShaders;
    }
}
