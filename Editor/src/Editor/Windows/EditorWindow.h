//
// Created by Andrew Graser on 9/6/2024.
//


#pragma once

#include <Core/Scene/ECS/Entity.h>

namespace GLE {
    class Scene;

    class EditorWindow {
    public:
        static void PushWindow(EditorWindow* window);
        static void PopWindow();

        static void SetSelectedEntity(const Entity& entity);
        static Entity GetSelectedEntity();

    public:
        EditorWindow(const std::string& name = "New Window") : mName(name) {}
        virtual ~EditorWindow() {
            for(auto& window : sActiveWindows) {
                delete window;
            }
        }

        const std::string& GetName() const {return mName;}

        void SetScene(const std::shared_ptr<Scene>& scene) {mActiveScene = scene;}

        virtual void ImGuiRender() = 0;
        static void RenderWindows();

    protected:
        std::shared_ptr<Scene> mActiveScene;

        std::string mName;


    private:
        static std::vector<EditorWindow*> sActiveWindows;
    };
}
