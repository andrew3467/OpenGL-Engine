//
// Created by Andrew Graser on 9/5/2024.
//

#include "SceneHeirarchy.h"

#include "imgui.h"
#include "Core/Scene/ECS/Component/Components.h"

namespace GLE {
    SceneHeirarchy::SceneHeirarchy() {

    }

    SceneHeirarchy::~SceneHeirarchy() {

    }

    void SceneHeirarchy::ImGuiRender() {


        ImGui::Begin("Scene Hierarchy");

        auto view = mActiveScene->mRegistry.view<NameComponent>();
        for(auto entityID : view) {
            Entity entity = {entityID, mActiveScene.get()};

            DrawEntityNode(entity);
        }

        ImGui::End();
    }

    void SceneHeirarchy::DrawEntityNode(Entity& entity) {
        auto& name = entity.GetComponent<NameComponent>().name;

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_Selected;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

        bool opened = ImGui::TreeNodeEx((void*)9817239, flags, name.c_str());
        if(ImGui::IsItemClicked()) {
            mSelectedEntity = entity;
        }

        if(opened) {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
            bool opened = ImGui::TreeNodeEx((void*)9817239, flags, name.c_str());
            if(opened) {
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }


    }
}
