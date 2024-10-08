//
// Created by apgra on 9/20/2024.
//

#include "LightSystem.h"

#include <Core/Scene/ECS/Component/Components.h>
#include "Renderer/Lights.h"
#include "Renderer/Renderer.h"

namespace GLE {

    LightSystem::LightSystem(Scene *scene) : System(scene)
    {
        GLE_INFO("Created Lighting System");
    }

    void LightSystem::Update()
    {
        auto lightEntities = mScene->mRegistry.group<PointLightComponent>();
        std::vector<PointLight> pointLights;

        for (auto e : lightEntities) {
            Entity entity {e, mScene};
            auto light = entity.GetComponent<PointLightComponent>().Light;
            light.Position = entity.GetComponent<TransformComponent>().Position;

            pointLights.push_back(light);
        }

        Renderer::SetPointLightData(pointLights);

        auto dirLightEntities = mScene->mRegistry.group<DirectionalLightComponent>();

        for(auto e : dirLightEntities) {
            Entity entity {e, mScene};
            auto& light = entity.GetComponent<DirectionalLightComponent>().Light;

            Renderer::SetDirLightData(light.Ambient, light.Direction);
        }
    }
}
