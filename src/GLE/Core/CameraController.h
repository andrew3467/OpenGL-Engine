//
// Created by Andrew Graser on 8/31/2024.
//

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H


namespace GLE {
    class Camera;


    class CameraController {
    public:
        CameraController() = default;
        ~CameraController() = default;

        void AddCamera(const std::shared_ptr<Camera>& camera) {mCamera = camera;}


        void Update(float dt);



    private:
        std::shared_ptr<Camera> mCamera;

        float mMoveSpeed = 10.f;
        float mSensitivity = 20.f;

        float mPrevX, mPrevY;
    };
}


#endif //CAMERACONTROLLER_H
