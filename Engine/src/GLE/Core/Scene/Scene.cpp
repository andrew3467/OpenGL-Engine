//
// Created by Andrew Graser on 9/2/2024.
//

#include "Scene.h"

#include <glm/gtx/string_cast.hpp>
#include <Core/Scene/Systems/RenderSystem.h>
#include <Core/Scene/Systems/LightSystem.h>

#include "Core/Util/UUID.h"

#include "ECS/Component/Components.h"
#include "ECS/Entity.h"
#include "Renderer/Renderer.h"


namespace GLE {
    Scene::Scene() {
        //mSystems.emplace_back(new LightSystem(this));
        mSystems.emplace_back(new RenderSystem(this));
    }

    Scene::~Scene() {
        for(int i = 0; i < mSystems.size(); i++) {
            delete mSystems[i];
        }
    }

    void Scene::Update(float dt) {
        for(auto& sys : mSystems) {
            sys->Update();
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
