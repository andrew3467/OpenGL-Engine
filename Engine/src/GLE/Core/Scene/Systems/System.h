//
// Created by apgra on 9/20/2024.
//

#pragma once

#include <Core/Scene/Scene.h>

namespace GLE {
    class System {
    public:
        System(Scene* scene) : mScene(scene) {}
        virtual ~System() = default;

        System(const System& other) = delete;


        virtual void Update() = 0;

    protected:
        Scene* mScene;
    };
}