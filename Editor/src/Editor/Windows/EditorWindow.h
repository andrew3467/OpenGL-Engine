//
// Created by Andrew Graser on 9/6/2024.
//


#pragma once

namespace GLE {
    class Scene;

    class EditorWindow {
    public:
        static void PushWindow(EditorWindow* window);
        static void PopWindow();

    public:
        EditorWindow() = default;
        virtual ~EditorWindow() {
            for(auto& window : sActiveWindows) {
                delete window;
            }
        }

        void SetScene(const std::shared_ptr<Scene>& scene) {mActiveScene = scene;}

        virtual void ImGuiRender() = 0;
        static void RenderWindows();

    protected:
        std::shared_ptr<Scene> mActiveScene;


    private:
        static std::vector<EditorWindow*> sActiveWindows;
    };
}
