//
// Created by apgra on 9/20/2024.
//

#include <Core/Scene/ECS/Component/Components.h>
#include <Renderer/Renderer.h>
#include "RenderSystem.h"
#include "Core/Scene/Scene.h"
#include "Core/Scene/ECS/Entity.h"


namespace GLE {

    RenderSystem::RenderSystem(Scene *scene) : System(scene)
    {
        GLE_INFO("Created Render System");
    }

    void RenderSystem::Update()
    {
        auto entitiesToRender = mScene->mRegistry.group<PrimitiveRendererComponent, TransformComponent>();

        for(auto e : entitiesToRender) {
            Entity entity = {e, mScene};

            auto& transform = entity.GetComponent<TransformComponent>();
            auto& renderer = entity.GetComponent<PrimitiveRendererComponent>();

            if(entity.HasComponent<MaterialComponent>()) {
                auto materialID = entity.GetComponent<MaterialComponent>().matID;

                Renderer::BindMaterial(materialID);
                Renderer::SubmitPrimitive(renderer.RenderType, materialID, transform);
                Renderer::UnbindMaterial(materialID);
            }
            else {
                GLE_WARN("Tried to render entity with no material");
            }
        }
    }
}