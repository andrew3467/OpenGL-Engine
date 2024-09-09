//
// Created by Andrew Graser on 9/6/2024.
//

#include "InspectorWindow.h"

#include "Core/Scene/ECS/Component/Components.h"

#include "imgui.h"
#include "SceneHeirarchy.h"


namespace GLE {
    InspectorWindow::InspectorWindow() {

    }

    InspectorWindow::~InspectorWindow() {

    }

    void InspectorWindow::ImGuiRender() {

        ImGui::Begin("Inspector");

        if(!SceneHeirarchy::mSelectedEntity) {
            ImGui::End();
            return;
        }

        //Transform
        auto& transform = SceneHeirarchy::mSelectedEntity.GetComponent<TransformComponent>();
        ImGui::DragFloat3("Position", &transform.Position.x, 0.1f);
        ImGui::DragFloat3("Rotation", &transform.Rotation.x, 0.1f);
        ImGui::DragFloat3("Scale", &transform.Scale.x, 0.1f);

        ImGui::End();
    }
}
