//
// Created by Andrew Graser on 8/31/2024.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"

#include "Core/Scene/ECS/Entity.h"

namespace GLE {
    struct TransformComponent {
        glm::vec3 Position = {0, 0, 0};
        glm::vec3 Rotation = {0, 0, 0};
        glm::vec3 Scale = {1, 1, 1};


    private:
        Entity Parent;
        std::vector<Entity> Children = {};

    public:

        void SetParent(Entity parent) {
            Parent = parent;
        }
        Entity GetParent() {return Parent;}

        void AddChild(Entity child) {Children.push_back(child);}
        std::vector<Entity> GetChildren() {return Children;}



        TransformComponent(glm::vec3 position) : Position(position) {}
        TransformComponent(const TransformComponent &other) = default;
        TransformComponent() = default;

        [[nodiscard]] glm::mat4 GetTransform() {
            glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));
            glm::mat4 translation = glm::translate(glm::mat4(1), Position)
            * rotation
            * glm::scale(glm::mat4(1), Scale);


            if(Parent.GetHandle() == entt::null || Parent.GetScene() == nullptr) return translation;

            auto parentTrans = Parent.GetComponent<TransformComponent>().GetTransform();
            return translation * parentTrans;
        }

        operator glm::mat4() {return GetTransform();}

    };
}

#endif //TRANSFORMCOMPONENT_H
