//
// Created by Andrew Graser on 9/6/2024.
//

#include "EditorWindow.h"


namespace GLE {
    std::vector<EditorWindow*> EditorWindow::sActiveWindows;
    Entity sSelectedEntity;
    MaterialID sSelectedAsset;

    void EditorWindow::PushWindow(EditorWindow *window) {
        sActiveWindows.push_back(window);
    }

    void EditorWindow::PopWindow() {
        sActiveWindows.pop_back();
    }

    void EditorWindow::RenderWindows() {
        for(auto& window : sActiveWindows) {
            window->ImGuiRender();
        }
    }

    void EditorWindow::SetSelectedEntity(const Entity &entity)
    {
        sSelectedEntity = entity;
    }

    Entity EditorWindow::GetSelectedEntity()
    {
        return sSelectedEntity;
    }

    void EditorWindow::SetSelectedAsset(MaterialID id)
    {
        sSelectedAsset = id;
    }

    MaterialID EditorWindow::GetSelectedAsset()
    {
        return sSelectedAsset;
    }
}
