//
// Created by apgra on 9/19/2024.
//

#pragma once


namespace GLE {
    struct Light {
        glm::vec3 Ambient = {1,1,1};
    };

    struct PointLight : Light {
        glm::vec3 Position = {0,0,0};
    };

    struct DirectionalLight : Light {

    };

    struct SpotLight : Light {

    };
}