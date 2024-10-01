//
// Created by apgra on 10/1/2024.
//

#include "AssetBrowserWindow.h"
#include "Renderer/Material.h"

#include <imgui.h>


namespace GLE {

    AssetBrowserWindow::AssetBrowserWindow()
        : EditorWindow("Asset Browser")
    {

    }

    AssetBrowserWindow::~AssetBrowserWindow()
    {

    }

    void AssetBrowserWindow::ImGuiRender()
    {
        ImGui::Begin(mName.c_str());

        //Render Materials
        {
            auto materials =  Material::GetMaterials();
            for(auto& mat : materials) {
                if(ImGui::Button("Material Icon"))
                {
                    ImGui::OpenPopup("Material Icon");
                }

                if(ImGui::BeginPopup("Material Icon")) {
                    char buffer[256];
                    memset(buffer, 0, sizeof(buffer));
                    strncpy_s(buffer, mat->GetName().c_str(), sizeof(buffer));

                    if(ImGui::InputText("##Name", buffer, sizeof(buffer))) {
                        mat->SetName(buffer);
                    }


                    ImGui::EndPopup();
                }
            }
        }

        ImGui::End();
    }
}