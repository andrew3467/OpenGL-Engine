//
// Created by Andrew Graser on 9/13/2024.
//


#pragma once

#include "Renderer/Material.h"



namespace GLE {

    struct MaterialComponent {
        MaterialComponent() {
            matID = Material::DefaultMaterial;
        }
        MaterialComponent(const MaterialComponent&) {}
        ~MaterialComponent()  {}

        MaterialID matID = 0;
    };
}
