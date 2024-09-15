//
// Created by Andrew Graser on 9/13/2024.
//


#pragma once
#include "Renderer/Material.h"


namespace GLE {
    struct MaterialComponent {
        MaterialComponent() {Material = new class Material;}
        MaterialComponent(const MaterialComponent&) = default;
        ~MaterialComponent() {delete Material;}


        Material *Material = nullptr;
    };
}
