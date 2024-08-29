//
// Created by Andrew Graser on 8/27/2024.
//

#include "Camera.h"
#include "glm/ext/matrix_transform.hpp"

#include "Glad/glad.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtx/string_cast.hpp"

#define CAMERA_MIN_PITCH -89.0f
#define CAMERA_MAX_PITCH 89.0f

namespace GLE {
    Camera::Camera(const glm::vec3 &position)
        : mPosition(position)
    {
        GLE_INFO("Created Orthographic camera at position: {0}", glm::to_string(position));
        RecalculateMatrices();
    }

    Camera::~Camera() {

    }

    void Camera::Move(MoveDir dir, float val) {
        switch (dir) {
            case MoveDir::Forward:
                mPosition += mFront * val;
                break;
            case MoveDir::Backward:
                mPosition += -mFront * val;
                break;
            case MoveDir::Right:
                mPosition += mRight * val;
                break;
            case MoveDir::Left:
                mPosition += -mRight * val;
                break;
        }

        RecalculateMatrices();
    }

    void Camera::Rotate(float yawOffset, float pitchOffset) {
        mYaw += yawOffset;
        mPitch += pitchOffset;

        mPitch = glm::clamp(mPitch, CAMERA_MIN_PITCH, CAMERA_MAX_PITCH);

        RecalculateMatrices();
    }

    void Camera::RecalculateMatrices() {
        glm::ivec4 viewport;
        glGetIntegerv(GL_VIEWPORT, &viewport.x);
        float aspect = (float)viewport.z / (float)viewport.w;



        glm::vec3 front = {
                cos(glm::radians(mYaw)) * cos(glm::radians(mPitch)),
                sin(glm::radians(mPitch)),
                sin(glm::radians(mYaw)) * cos(glm::radians(mPitch))
        };
        mFront = glm::normalize(front);


        const glm::vec3 worldUp = {0,1,0};
        mRight = glm::normalize(glm::cross(mFront, worldUp));
        mUp = glm::normalize(glm::cross(mRight, mFront));

        mView = glm::lookAt(mPosition, mPosition + mFront, mUp);
        mProjection = glm::perspective(glm::radians(mFOV), aspect, mNear, mFar);
        mViewProj = mProjection * mView;
    }
}
