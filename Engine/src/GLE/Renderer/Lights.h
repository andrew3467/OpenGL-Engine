//
// Created by apgra on 9/19/2024.
//

#pragma once


namespace GLE {
    struct Light {
        glm::vec3 Ambient;
    };

    struct PointLight : Light {
        glm::vec3 Position;
    };

    struct DirectionalLight : Light {

    };

    struct SpotLight : Light {

    };
}