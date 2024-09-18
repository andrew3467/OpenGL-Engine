//
// Created by Andrew Graser on 9/13/2024.
//


#pragma once

#include "Renderer/Material.h"



namespace GLE {

    struct MaterialComponent {
        MaterialComponent() : Material(std::make_shared<GLE::Material>()) {}
        MaterialComponent(const MaterialComponent&) = delete;
        ~MaterialComponent()  {}


        std::shared_ptr<Material> Material;
    };
}
