//
// Created by Andrew Graser on 9/6/2024.
//

#include "InspectorWindow.h"

#include "Core/Scene/ECS/Component/Components.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "SceneHierarchy.h"


namespace GLE {
    InspectorWindow::InspectorWindow() {

    }

    InspectorWindow::~InspectorWindow() {

    }

    void InspectorWindow::ImGuiRender() {

        ImGui::Begin("Inspector");

        if(!SceneHierarchy::mSelectedEntity) {
            ImGui::End();
            return;
        }

        auto& curEntity = SceneHierarchy::mSelectedEntity;

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_Selected;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;



        //Name

        {
            auto& name = curEntity.GetComponent<NameComponent>();

            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strncpy_s(buffer, name.name.c_str(), sizeof(buffer));

            if(ImGui::InputText("##Name", buffer, sizeof(buffer))) {
                name.name = std::string(buffer);
            }
        }

        //Add Component
        if(ImGui::Button("Add Component")) {
            ImGui::OpenPopup("Add Component");
        }

        if(ImGui::BeginPopup("Add Component")) {
            AddComponentDisplay<TransformComponent>("Transform");
            AddComponentDisplay<PrimitiveRendererComponent>("Primitive Renderer");
            AddComponentDisplay<CameraComponent>("Camera");
            AddComponentDisplay<MaterialComponent>("Material");


            ImGui::EndPopup();
        }



        //Transform
        bool enabled = ImGui::TreeNodeEx((void*)0, flags, "Transform");
        if(enabled) {
            auto& transform = curEntity.GetComponent<TransformComponent>();

            DrawVec3("Position", transform.Position);
            DrawVec3("Rotation", transform.Rotation);
            DrawVec3("Scale", transform.Scale);
            ImGui::TreePop();
        }

        if(curEntity.HasComponent<PrimitiveRendererComponent>()){
            enabled = ImGui::TreeNodeEx((void*)1,flags, "Primitive Renderer");
            if(enabled) {
                ImGuiComboFlags flags = ImGuiComboFlags_NoPreview | ImGuiComboFlags_HeightRegular;

                const char* items[] = {"Cube", "Sphere", "Capsule"};
                static const char* curItem = items[0];

                auto& renderer = curEntity.GetComponent<PrimitiveRendererComponent>();
                if(ImGui::BeginCombo(curItem, "", flags)) {

                    for(int i = 0; i < IM_ARRAYSIZE(items); i++) {
                        bool selected = curItem == items[i];

                        if(ImGui::Selectable(items[i], selected)) {
                            curItem = items[i];
                            renderer.RenderType = (PrimitiveType)i;
                        }

                        if(selected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }

                    ImGui::EndCombo();
                }

                ImGui::TreePop();
            }
        }

        if(curEntity.HasComponent<CameraComponent>()) {
            enabled = ImGui::TreeNodeEx((void*)2,flags, "Camera");
            if(enabled) {

                auto pos = curEntity.GetComponent<CameraComponent>().Camera->GetPosition();
                ImGui::InputFloat3("Position", &pos.x);

                ImGui::TreePop();
            }
        }

        if(curEntity.HasComponent<MaterialComponent>()) {
            enabled = ImGui::TreeNodeEx((void*)3,flags, "Material");
            if(enabled) {
                auto material = curEntity.GetComponent<MaterialComponent>().Material;

                glm::vec3 color = material->Albedo;
                ImGui::ColorPicker3("Albedo", &color.x);
                material->Albedo = color;

                ImGui::Text("Albedo Map");
                ImGui::SameLine();
                DrawTextureSelectionWindow((void*)material->AlbedoMap.get(), "Albedo Map");

                ImGui::Text("Normal Map");
                ImGui::SameLine();
                DrawTextureSelectionWindow((void*)material->AlbedoMap.get(), "Normal Map");

                ImGui::Text("Diffuse Map");
                ImGui::SameLine();
                DrawTextureSelectionWindow((void*)material->AlbedoMap.get(), "Diffuse Map");

                ImGui::TreePop();
            }
        }

        ImGui::End();
    }

    void InspectorWindow::DrawVec3(const std::string &name, glm::vec3 &vec) {
        auto& io = ImGui::GetIO();
        auto font = io.Fonts->Fonts[0];

        ImGui::PushID(name.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, 100.0f);
        ImGui::Text(name.c_str());
        ImGui::NextColumn();

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));

        ImGui::PushFont(font);
        ImGui::Button("X", buttonSize);
        ImGui::PopFont();
        ImGui::PopStyleColor(1);

        ImGui::SameLine();
        ImGui::DragFloat("##x", &vec.x, 0.01f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));

        ImGui::PushFont(font);
        ImGui::Button("Y", buttonSize);
        ImGui::PopFont();
        ImGui::PopStyleColor(1);

        ImGui::SameLine();
        ImGui::DragFloat("##y", &vec.y, 0.01f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 1.0f, 1.0f));

        ImGui::PushFont(font);
        ImGui::Button("Z", buttonSize);
        ImGui::PopFont();
        ImGui::PopStyleColor(1);

        ImGui::SameLine();
        ImGui::DragFloat("##z", &vec.y, 0.01f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::Columns();
        ImGui::PopID();
    }

    void InspectorWindow::DrawTextureSelectionWindow(void *dest, const std::string &title)
    {
        if(ImGui::Button(title.c_str()))
        {
            ImGui::OpenPopup("Texture Selection");
        }

        if(ImGui::BeginPopup("Texture Selection"))
        {
            ImGui::Text("Texture selector");

            ImGui::EndPopup();
        }
    }

    template<typename C>
    void InspectorWindow::AddComponentDisplay(const std::string& name)
    {
        auto& selection = SceneHierarchy::mSelectedEntity;
        if(selection.GetHandle() != entt::null) {
            if(!selection.HasComponent<C>()) {
                if(ImGui::MenuItem(name.c_str())) {
                    selection.AddComponent<C>();
                }
            }
        }
    }
}
