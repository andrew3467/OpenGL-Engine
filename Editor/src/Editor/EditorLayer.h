//
// Created by Andrew Graser on 9/4/2024.
//


#pragma once

#include "Windows/SceneHierarchy.h"
#include "GLE/Core/Layer.h"


class Event;

namespace GLE {
    class EditorLayer : public Layer {
    public:
        EditorLayer() : Layer("EditorLayer") {}
        ~EditorLayer() override = default;

        void OnEvent(Event &e) override;

        void OnCreate() override;
        void OnRun() override;
        void OnUpdate(float dt) override;
        void OnImGuiRender() override;

    private:
        SceneHierarchy mSceneHeirarchy;
        std::shared_ptr<Scene> mScene;
    };
}
