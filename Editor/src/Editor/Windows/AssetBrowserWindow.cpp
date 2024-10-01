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
                ImGui::Button(mat->GetName().c_str());
            }
        }

        ImGui::End();
    }
}