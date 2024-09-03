//
// Created by Andrew Graser on 8/31/2024.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "BaseComponent.h"
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

namespace GLE {
    struct TransformComponent : BaseComponent {
        glm::vec3 Position = {0,0,0};
        glm::vec3 Rotation = {0,0,0};
        glm::vec3 Scale = {1,1,1};

        TransformComponent(glm::vec3 position) : Position(position) {}
        TransformComponent(const TransformComponent &other) = default;
        TransformComponent() = default;

        glm::mat4 GetTransform() const {
            glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

            return glm::translate(glm::mat4(1), Position)
            * rotation
            * glm::scale(glm::mat4(1), Scale);
        }

    };
}

#endif //TRANSFORMCOMPONENT_H
