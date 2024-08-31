//
// Created by Andrew Graser on 8/31/2024.
//

#include "CameraController.h"

#include "Application.h"
#include "Input.h"

#include "GLFW/glfw3.h"
#include "Renderer/Camera.h"


namespace GLE {
    void CameraController::Update(float dt) {
        if(GLE::Input::GetKey(GLFW_KEY_W)) {
            mCamera->ProcessKeyboard(GLE::MoveDir::FORWARD, dt, mMoveSpeed);
        }
        if(GLE::Input::GetKey(GLFW_KEY_S)) {
            mCamera->ProcessKeyboard(GLE::MoveDir::BACKWARD, dt, mMoveSpeed);
        }
        if(GLE::Input::GetKey(GLFW_KEY_A)) {
            mCamera->ProcessKeyboard(GLE::MoveDir::LEFT, dt, mMoveSpeed);
        }
        if(GLE::Input::GetKey(GLFW_KEY_D)) {
            mCamera->ProcessKeyboard(GLE::MoveDir::RIGHT, dt, mMoveSpeed);
        }
        if(GLE::Input::GetKey(GLFW_KEY_E)) {
            mCamera->ProcessKeyboard(GLE::MoveDir::UP, dt, mMoveSpeed);
        }
        if(GLE::Input::GetKey(GLFW_KEY_Q)) {
            mCamera->ProcessKeyboard(GLE::MoveDir::DOWN, dt, mMoveSpeed);
        }

        static bool firstMouse = true;
        static bool firstScrollDown = true;

        if(GLE::Input::GetMouseButton(GLFW_MOUSE_BUTTON_MIDDLE)) {
            GLE::Application::Get().GetWindow().ToggleCursor(false);

            auto [x,y] = GLE::Input::GetMousePosition();
            if(firstMouse) {
                mPrevX = x;
                mPrevY = y;
                firstMouse = false;
            }

            if (firstScrollDown) {
                GLE::Input::SetMousePosition(mPrevX, mPrevY);
                firstScrollDown = false;
            }

            float xOffset = x - mPrevX;
            float yOffset = mPrevY - y;

            const float sensitivity = 2.f;
            mCamera->ProcessMouseMovement(xOffset, yOffset, sensitivity * dt);
            mPrevX = x;
            mPrevY = y;
        }else {
            GLE::Application::Get().GetWindow().ToggleCursor(true);
            firstScrollDown = true;
        }
    }
}
