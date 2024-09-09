//
// Created by Andrew Graser on 8/31/2024.
//

#pragma once

#include "Core/Scene/Scene.h"


namespace GLE {

    class Entity {
    public:
        Entity();
        Entity(entt::entity handle, Scene* scene);
        Entity(const Entity& other);

        ~Entity() = default;

        entt::entity GetHandle() const {return mEntityHandle;}


        void Destroy() {
            if(mEntityHandle == entt::null) return;

            mScene->mRegistry.destroy(mEntityHandle);
        }

        template <typename C>
        C& GetComponent() {
            return mScene->mRegistry.get<C>(mEntityHandle);
        }

        template <typename C>
        bool HasComponent() const {
            return mScene->mRegistry.all_of<C>(mEntityHandle);
        }

        template <typename C, typename ... Args>
        C& AddComponent(Args&... args) {
            C& component = mScene->mRegistry.emplace<C>(mEntityHandle, std::forward<Args>(args)...);
            return component;
        }

        operator bool() const { return mEntityHandle != entt::null; }

    private:
        entt::entity mEntityHandle;
        Scene* mScene = nullptr;
    };
}
