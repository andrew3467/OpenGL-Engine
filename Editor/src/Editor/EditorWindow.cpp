//
// Created by Andrew Graser on 9/6/2024.
//

#include "EditorWindow.h"


namespace GLE {
    std::vector<EditorWindow*> EditorWindow::sActiveWindows;


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
}
