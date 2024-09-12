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

        void ImGuiRender() override;


    private:
        void DrawEntityNode(Entity& entity);

    private:
        friend class Scene;

    public:
        static Entity mSelectedEntity;
    };
}
