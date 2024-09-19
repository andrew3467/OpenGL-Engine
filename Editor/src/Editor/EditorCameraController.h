//
// Created by Andrew Graser on 9/15/2024.
//


#pragma once

#include "Renderer/Camera.h"

namespace GLE {
    class EditorCameraController {
    public:
        EditorCameraController();
        ~EditorCameraController();

        void Init();

        Camera& GetCamera() {return *mCamera;}

        void Update(float dt);

        [[nodiscard]] const glm::vec3& GetPosition() const {return mCamera->GetPosition();}

    private:
        std::shared_ptr<Camera> mCamera;

        float mMoveSpeed = 10.f;
        float mSensitivity = 10.f;

        float mPrevX, mPrevY;
    };
}
