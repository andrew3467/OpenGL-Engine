//
// Created by Andrew Graser on 8/31/2024.
//

#ifndef ENTITY_H
#define ENTITY_H


#include "Core/Scene/Scene.h"


namespace GLE {
    class Scene;

    class Entity {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);
        Entity(const Entity& other);

        ~Entity() = default;



        template <typename C, typename ... Args>
        C& AddComponent(Args&&... args) {
            C& component = mScene->mRegistry.emplace<C>(std::forward<Args>(args)...);
            return component;
        }


    private:
        entt::entity mEntityHandle;
        Scene* mScene = nullptr;
    };
}



#endif //ENTITY_H