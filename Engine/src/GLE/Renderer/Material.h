//
// Created by Andrew Graser on 9/13/2024.
//


#pragma once
#include <glm/vec3.hpp>

#include "Shader.h"
#include "Texture.h"

#include "Core/Util/UUID.h"

namespace GLE {
    typedef UUID MaterialID;

    class Material {
    public:
        static MaterialID Create();
        static std::shared_ptr<Material> Get(MaterialID id);
        static std::vector<std::shared_ptr<Material>> GetMaterials();
        static std::vector<MaterialID> GetIDS();

        static MaterialID DefaultMaterial;

    public:

        Material()
            : mName("New Material")
        {
            Shader = Shader::Get("Standard");
            
            AlbedoMap = Texture2D::Get("Default");
            NormalMap = Texture2D::Get("Default");
            DiffuseMap = Texture2D::Get("Default");
        }

        Material(const Material&) = default;
        ~Material() = default;

        void SetName(const std::string& name) {mName = name;}
        const std::string& GetName() const {return mName;}

        [[nodiscard]] MaterialID GetID() const {return mID;}


        std::string mName;

        std::shared_ptr<Shader> Shader = nullptr;

        glm::vec3 Albedo = glm::vec3(1.0f, 1.0f, 1.0f);

        std::shared_ptr<Texture2D> AlbedoMap = nullptr;
        std::shared_ptr<Texture2D> NormalMap = nullptr;
        std::shared_ptr<Texture2D> DiffuseMap = nullptr;

    private:
        MaterialID mID;
    };
}
