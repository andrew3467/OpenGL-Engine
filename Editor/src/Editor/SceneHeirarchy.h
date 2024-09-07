//
// Created by Andrew Graser on 9/5/2024.
//


#pragma once

#include "EditorWindow.h"
#include "Core/Scene/ECS/Entity.h"
#include "GLE/Core/Scene/Scene.h"

namespace GLE {
    class SceneHeirarchy : public EditorWindow {
    public:
        SceneHeirarchy();
        ~SceneHeirarchy() override;

        void SetScene(const std::shared_ptr<Scene>& scene) {mActiveScene = scene;}

        void ImGuiRender() override;


    private:
        void DrawEntityNode(Entity& entity);

    private:
        std::shared_ptr<Scene> mActiveScene;

        Entity mSelectedEntity;

        friend class Scene;
        friend class InspectorWindow;
    };
}
