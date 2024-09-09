//
// Created by Andrew Graser on 8/31/2024.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"

namespace GLE {
    struct TransformComponent {
        glm::vec3 Position = {0,0,0};
        glm::vec3 Rotation = {0,0,0};
        glm::vec3 Scale = {1,1,1};


    private:
        TransformComponent* Parent;
        std::vector<TransformComponent*> Children;

    public:

        void SetParent(TransformComponent* parent) {
            Parent = parent; parent->Children.push_back(this);
        }
        TransformComponent* GetParent() {return Parent;}

        void AddChild(TransformComponent* child) {Children.push_back(child); child->SetParent(this);}
        std::vector<TransformComponent*> GetChildren() {return Children;}



        TransformComponent(glm::vec3 position) : Position(position) {}
        TransformComponent(const TransformComponent &other) = default;
        TransformComponent() = default;

        glm::mat4 GetTransform() const {
            glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));
            glm::mat4 translation = glm::translate(glm::mat4(1), Position)
            * rotation
            * glm::scale(glm::mat4(1), Scale);

            GLE_ASSERT(Parent != this, "Parent == this");

            if(Parent == nullptr) {
                return translation;
            }

            return translation * Parent->GetTransform();
        }

        operator glm::mat4() const {return GetTransform();}

    };
}

#endif //TRANSFORMCOMPONENT_H
