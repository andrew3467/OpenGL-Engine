//
// Created by Andrew Graser on 9/2/2024.
//

#include "Scene.h"

#include <glm/gtx/string_cast.hpp>

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

    void Scene::Render() {
        auto entitiesToRender = mRegistry.group<PrimitiveRendererComponent, TransformComponent>();

        for(auto e : entitiesToRender) {
            Entity entity = {e, this};

            auto& transform = entity.GetComponent<TransformComponent>();
            auto& renderer = entity.GetComponent<PrimitiveRendererComponent>();


            if(entity.HasComponent<MaterialComponent>()) {
                auto& material = entity.GetComponent<MaterialComponent>().Material;
                Renderer::BindMaterial(*material);
                Renderer::SubmitPrimitive(renderer.RenderType, *material->Shader, transform);
            }
            else {
                GLE_WARN("Tried to render entity with no material");
            }
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

        return entity;

    }
}
