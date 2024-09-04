//
// Created by Andrew Graser on 9/2/2024.
//

#include "Scene.h"

#include "Core/Util/UUID.h"

#include "ECS/Component/Components.h"
#include "ECS/Entity.h"
#include "Renderer/Renderer.h"


namespace GLE {
    Scene::Scene() {

    }
    Scene::~Scene() {

    }

    void Scene::Update(float dt) {

    }

    void Scene::Render(Shader& shader) {
        auto entitiesToRender = mRegistry.group<PrimitiveRendererComponent, TransformComponent>();

        for(auto entity : entitiesToRender) {
            auto [renderer, transform] =
                entitiesToRender.get<PrimitiveRendererComponent, TransformComponent>(entity);

            Renderer::SubmitPrimitive(renderer.RenderType, shader, transform);
        }
    }

    Entity Scene::CreateEntity(const std::string &name) {
        return CreateEntityWithUUID(UUID(), name);
    }

    Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string &name) {
        Entity entity = {mRegistry.create(), this};
        entity.AddComponent<IDComponent>(uuid);
        entity.AddComponent<NameComponent>(name);
        entity.AddComponent<TransformComponent>();

        //Add to map of all entities

        return entity;

    }
}
