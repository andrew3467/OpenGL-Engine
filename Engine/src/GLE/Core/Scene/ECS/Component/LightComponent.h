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
        ~LightComponent() {
            delete mLight;
        }
        
        void Create(LightType type) {
            switch (type)
            {
                case LightType::Point:      delete mLight; mLight = new PointLight; break;
                case LightType::Directional:    delete mLight; mLight = new DirectionalLight; break;
                case LightType::Spot:            delete mLight; mLight = new SpotLight; break;
            }
        }



        LightType Type = LightType::Point;

    private:
        Light* mLight;
    };
}