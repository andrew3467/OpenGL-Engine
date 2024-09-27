//
// Created by Andrew Graser on 9/13/2024.
//


#pragma once
#include <glm/vec3.hpp>

#include "Shader.h"
#include "Texture.h"

namespace GLE {
    class Material {
    public:
        static std::shared_ptr<Material> Create() {return std::make_shared<Material>(); }

        Material() {
            Shader = Shader::Get("Standard");
            
            AlbedoMap = Texture2D::Get("Default");
            NormalMap = Texture2D::Get("Default");
            DiffuseMap = Texture2D::Get("Default");
        }
        Material(const Material&) = delete;

        ~Material() = default;



    public:
        std::shared_ptr<Shader> Shader = nullptr;

        glm::vec3 Albedo = glm::vec3(1.0f, 1.0f, 1.0f);

        std::shared_ptr<Texture2D> AlbedoMap = nullptr;
        std::shared_ptr<Texture2D> NormalMap = nullptr;
        std::shared_ptr<Texture2D> DiffuseMap = nullptr;
    };
}
