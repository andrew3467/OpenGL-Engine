//
// Created by apgra on 9/19/2024.
//

#pragma once


namespace GLE {
    struct PointLight {
        glm::vec3 Ambient = {1,1,1};
        glm::vec3 Position = {0,0,0};

        float Constant = 1;
        float Linear = 1;
        float Quadratic = 1;
    };

    struct DirectionalLight {
        glm::vec3 Ambient = {1,1,1};
        glm::vec3 Direction = {45, 90, 45};      //Measured in degrees
    };

    struct SpotLight {
        glm::vec3 Ambient = {1,1,1};
    };
}