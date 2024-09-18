//
// Created by Andrew Graser on 9/5/2024.
//

#include "SceneHierarchy.h"

#include "Core/Scene/ECS/Component/Components.h"

#include "imgui.h"
#include "imgui_internal.h"


namespace GLE
{
    Entity SceneHierarchy::mSelectedEntity;

    SceneHierarchy::SceneHierarchy()
    {

    }

    SceneHierarchy::~SceneHierarchy()
    {

    }

    void SceneHierarchy::ImGuiRender()
    {


        ImGui::Begin("Scene Hierarchy");

        //Deselect
        if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
        {
            mSelectedEntity = {};
        }

        // Right-click on blank space
        if (ImGui::BeginPopupContextWindow("Create Entity", ImGuiPopupFlags_MouseButtonRight))
        {
            ImGui::MenuItem("Create", nullptr, false, false);
            if (ImGui::BeginMenu("Create Entity"))
            {
                if (ImGui::MenuItem("Empty"))
                {
                    mActiveScene->CreateEntity("Empty");
                }
                if (ImGui::MenuItem("Cube"))
                {
                    auto entity = mActiveScene->CreateEntity("Cube");
                    entity.AddComponent<PrimitiveRendererComponent>().RenderType = PrimitiveType::Cube;
                    entity.AddComponent<MaterialComponent>();
                }

                ImGui::EndMenu();
            }


            ImGui::EndPopup();
        }


        auto view = mActiveScene->mRegistry.view<NameComponent>();
        for (auto entityID: view)
        {
            Entity entity = {entityID, mActiveScene.get()};

            //Don't draw new tree if entity is a child
            if(entity.GetComponent<TransformComponent>().GetParent().GetHandle() == entt::null) {
                DrawEntityNode(entity);
            }
        }

        ImGui::End();
    }

    void SceneHierarchy::DrawEntityNode(Entity &entity)
    {
        auto &name = entity.GetComponent<NameComponent>().name;

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_Selected;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

        bool opened = ImGui::TreeNodeEx((void*)entity.GetHandle(), flags, name.c_str());
        if (ImGui::IsMouseDown(0) && ImGui::IsItemClicked())
        {
            mSelectedEntity = entity;
        }


        //Delete Entity Popup
        if (ImGui::IsItemClicked(1))
        {
            ImGui::OpenPopup("Delete");
            if (ImGui::BeginPopup("Delete"))
            {
                ImGui::MenuItem("Delete", nullptr, false, false);
                if (ImGui::BeginMenu("Delete Entity"))
                {
                    entity.Destroy();
                    ImGui::EndMenu();
                }


                ImGui::EndPopup();
            }
        }

        if (opened)
        {
            auto transform = entity.GetComponent<TransformComponent>();
            for (auto child : transform.GetChildren())
            {
                DrawEntityNode(child);
            }


            ImGui::TreePop();
        }
    }
}