//
// Created by Andrew Graser on 8/31/2024.
//

#pragma once

#include "Core/Scene/Scene.h"


namespace GLE {

    class Entity {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);
        Entity(const Entity& other);

        ~Entity() = default;


        template <typename C>
        C& GetComponent() {
            return mScene->mRegistry.get<C>(mEntityHandle);
        }

        template <typename C, typename ... Args>
        C& AddComponent(Args&... args) {
            C& component = mScene->mRegistry.emplace<C>(mEntityHandle, std::forward<Args>(args)...);
            return component;
        }

    private:
        entt::entity mEntityHandle;
        Scene* mScene = nullptr;
    };
}
