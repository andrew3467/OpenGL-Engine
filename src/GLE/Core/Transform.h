//
// Created by Andrew Graser on 8/31/2024.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "glm/vec3.hpp"

namespace GLE {
    struct Transform {
        glm::vec3 Position;
        glm::vec3 Rotation;
        glm::vec3 Scale;
    };
}

#endif //TRANSFORM_H
