//
// Created by Andrew Graser on 9/6/2024.
//


#pragma once

namespace GLE {
    class EditorWindow {
    public:
        static void PushWindow(EditorWindow* window);
        static void PopWindow();

    public:
        EditorWindow() = default;
        virtual ~EditorWindow() = default;

        virtual void ImGuiRender() = 0;
        static void RenderWindows();


    private:
        static std::vector<EditorWindow*> sActiveWindows;
    };
}
