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

                if(ImGui::Button(mat->GetName().c_str()))
                {
                    EditorWindow::SetSelectedEntity({});
                    EditorWindow::SetSelectedAsset(mat->GetID());
                }
            }
        }

        ImGui::End();
    }
}