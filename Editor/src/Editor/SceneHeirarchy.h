//
// Created by Andrew Graser on 9/5/2024.
//


#pragma once

#include "GLE/Core/Scene/Scene.h"

namespace GLE {
    class SceneHeirarchy {
    public:
        SceneHeirarchy();
        ~SceneHeirarchy() = default;

        void SetScene(const std::shared_ptr<Scene>& scene) {mActiveScene = scene;}

        void Render();


    private:
        std::shared_ptr<Scene> mActiveScene;

        friend class Scene;
    };
}
