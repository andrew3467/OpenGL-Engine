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
        auto lightEntities = mScene->mRegistry.group<LightComponent>();
        std::vector<glm::vec3> pointLights;
        std::vector<glm::vec3> positions;

        for (auto e : lightEntities) {
            Entity entity {e, mScene};
            auto& lightcomp = entity.GetComponent<LightComponent>();
            auto& transformcomp = entity.GetComponent<TransformComponent>();

            pointLights.push_back(lightcomp.Light.Ambient);
            positions.push_back(transformcomp.Position);
        }

        Renderer::SetLightData(pointLights, positions);
    }
}
