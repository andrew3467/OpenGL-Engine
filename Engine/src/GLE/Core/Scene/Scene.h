//
// Created by Andrew Graser on 9/2/2024.
//

#pragma once

#include <entt/entt.hpp>

#include "Core/Time.h"


namespace GLE {
    class UUID;
    class Entity;
    class System;

    class Scene {
    public:
        Scene();
        ~Scene();

        void Update(float dt);

        Entity CreateEntity(const std::string& name = std::string());
        Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());

        template<typename C>
        std::vector<C> GetComponents() {
            std::vector<C> result;
            auto view = mRegistry.view<C>();

            for(auto& comp : view) {
                result.push_back(comp.second);
            }

            return result;
        }

    private:
        entt::registry mRegistry;

        std::vector<System*> mSystems;


        friend class Entity;
        friend class SceneHierarchy;
        friend class InspectorWindow;
        friend class RenderSystem;
        friend class LightSystem;
    };
}
