//
// Created by apgra on 9/20/2024.
//

#include "LightSystem.h"

#include <Core/Scene/ECS/Component/Components.h>
#include "Renderer/Lights.h"

namespace GLE {

    LightSystem::LightSystem(Scene *scene) : System(scene)
    {
        GLE_INFO("Created Lighting System");
    }

    void LightSystem::Update()
    {
        auto lightEntities = mScene->mRegistry.group<LightComponent>();
        std::vector<PointLight> pointLights;
        std::vector<glm::vec3> positions;

        for (auto e : lightEntities) {
            Entity entity {e, mScene};
            auto& lightcomp = entity.GetComponent<LightComponent>();
            auto& transformcomp = entity.GetComponent<TransformComponent>();

            pointLights.push_back(lightcomp.Light);
            positions.push_back(transformcomp.Position);
        }

        auto materialEntities = mScene->mRegistry.group<MaterialComponent>();

        for(auto e : materialEntities) {
            Entity entity = {e, mScene};

            auto& mat = entity.GetComponent<MaterialComponent>();
            auto& material = mat.Material;

            GLE_ASSERT(material != nullptr, "Material IS NULL");

            if(material == nullptr) {
                GLE_WARN("Material Component contains null material!");
                continue;
            }

            auto& shader = *material->Shader;

            shader.Bind();

            for(int i = 0; i < pointLights.size(); i++) {
                std::string index =
                        std::string("uPointLights[").
                                append(std::to_string(i)).
                                append("]");
                shader.SetPointLight(index, pointLights[i], positions[i]);
            }
        }
    }
}