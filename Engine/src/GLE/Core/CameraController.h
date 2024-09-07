//
// Created by Andrew Graser on 8/31/2024.
//

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include <glm/vec3.hpp>

#include "Renderer/Camera.h"


namespace GLE {


    class CameraController {
    public:
        CameraController() = default;
        ~CameraController() = default;

        void AddCamera(const std::shared_ptr<Camera>& camera) {mCamera = camera;}
        Camera& GetCamera() {return *mCamera;}


        void Update(float dt);

        const glm::vec3& GetPosition() const {return mCamera->GetPosition();}


    private:
        std::shared_ptr<Camera> mCamera;

        float mMoveSpeed = 10.f;
        float mSensitivity = 20.f;

        float mPrevX, mPrevY;
    };
}


#endif //CAMERACONTROLLER_H
