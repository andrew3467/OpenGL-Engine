//
// Created by Andrew Graser on 9/13/2024.
//


#pragma once

#include "Renderer/Material.h"



namespace GLE {

    struct MaterialComponent {
        MaterialComponent() {}
        MaterialComponent(const MaterialComponent&) {}
        ~MaterialComponent()  {}

        GLE::Material Material;
    };
}
