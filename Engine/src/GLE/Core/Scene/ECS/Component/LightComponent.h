//
// Created by apgra on 9/19/2024.
//

#pragma once

#include "Renderer/Lights.h"

namespace GLE {
    struct PointLightComponent {
        PointLightComponent() = default;
        PointLightComponent(const PointLightComponent&) = default;
        ~PointLightComponent() = default;

        PointLight Light;
    };

    struct DirectionalLightComponent {
        DirectionalLightComponent() = default;
        DirectionalLightComponent(const DirectionalLightComponent&) = default;
        ~DirectionalLightComponent() = default;

        DirectionalLight Light;
    };
}