//
// Created by apgra on 9/19/2024.
//

#pragma once

#include "Renderer/Lights.h"

namespace GLE {
    enum class LightType {
        Point,
        Directional,
        Spot
    };

    struct LightComponent {
        LightComponent() = default;
        LightComponent(const LightComponent&) = default;
        ~LightComponent() = default;

        PointLight Light;
    };
}