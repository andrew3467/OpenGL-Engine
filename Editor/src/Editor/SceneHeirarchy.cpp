//
// Created by Andrew Graser on 9/5/2024.
//

#include "SceneHeirarchy.h"

#include "imgui.h"
#include "Core/Scene/ECS/Component/TransformComponent.h"

namespace GLE {
    SceneHeirarchy::SceneHeirarchy() {

    }

    void SceneHeirarchy::Render() {
        auto transforms = mActiveScene->mRegistry.view<TransformComponent>();

        ImGui::Begin("Scene Heirarchy");

        ImGui::Text("Transform Count: %i", transforms.size());

        ImGui::End();
    }
}
