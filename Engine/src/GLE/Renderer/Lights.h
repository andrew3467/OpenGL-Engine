//
// Created by apgra on 9/19/2024.
//

#pragma once


namespace GLE {
    struct Light {
        glm::vec3 Ambient;
    };

    struct PointLight : public Light {
        glm::vec3 Position;
    };

    struct DirectionalLight : public Light {

    };

    struct SpotLight : public Light {

    };
}