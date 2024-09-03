//
// Created by Andrew Graser on 9/2/2024.
//

#include "Scene.h"

#include "Core/Util/UUID.h"
#include "ECS/Component/IDComponent.h"
#include "ECS/Component/NameComponent.h"
#include "ECS/Component/TransformComponent.h"


namespace GLE {
    Scene::Scene() {
        auto entity = mRegistry.create();


        mRegistry.emplace<NameComponent>(entity, "entt");
        mRegistry.emplace<TransformComponent>(entity);


        //get all entities with a Name
        auto view = mRegistry.view<NameComponent>();
        for(auto entity : view) {
            auto name = view.get<NameComponent>(entity);
            GLE_INFO("Entity Name: {0}", name);
        }

        //get the name of every entity that has a transform
        auto group = mRegistry.group<TransformComponent>(entt::get<NameComponent>);
        for(auto entity : group) {
            auto&[transform, name] = group.get<TransformComponent, NameComponent>(entity);
            GLE_INFO("Entity Name: {0}", name);
            GLE_INFO("Entity Transform: {0}", transform.Position.x);
        }
    }

    Scene::~Scene() {

    }

    Entity Scene::CreateEntity(const std::string &name) {
        return CreateEntityWithUUID(UUID(), name);
    }

    Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string &name) {
        Entity entity = {mRegistry.create(), this};
        entity.AddComponent<NameComponent>(name);
        entity.AddComponent<IDComponent>(uuid);

        //Add to map of all entities

        return entity;

    }
}
