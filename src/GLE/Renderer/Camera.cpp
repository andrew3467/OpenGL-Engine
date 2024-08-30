//
// Created by Andrew Graser on 8/27/2024.
//

#include "Camera.h"

#include "Glad/glad.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtx/string_cast.hpp"


namespace GLE {
#define CAMERA_MIN_ZOOM 1.0f
#define CAMERA_MAX_ZOOM 90.0f

#define CAMERA_MIN_PITCH -89.0f
#define CAMERA_MAX_PITCH 89.0f

    PerspectiveCamera::PerspectiveCamera()
            : PerspectiveCamera({0.0f, 0.0f, 0.0f}) {

    }

    PerspectiveCamera::PerspectiveCamera(const glm::vec3 &position)
            : mNear(0.1f), mFar(1000.0f) {
        RecalculateMatrices();

        SetPosition(position);
    }

    PerspectiveCamera::~PerspectiveCamera() {

    }

    void PerspectiveCamera::RecalculateMatrices() {
        glm::ivec4 viewport = {};
        glGetIntegerv(GL_VIEWPORT, &viewport.x);
        float aspect = (float)viewport.z / (float)viewport.w;


        glm::vec3 front = {
            cos(glm::radians(mYaw)) * cos(glm::radians(mPitch)),
            sin(glm::radians(mPitch)),
            sin(glm::radians(mYaw)) * cos(glm::radians(mPitch))
    };

        mFront = glm::normalize(front);

        mRight = glm::normalize(glm::cross(mFront, mWorldUp));
        mUp = glm::normalize(glm::cross(mRight, mFront));

        mView = glm::lookAt(mPosition, mPosition + mFront, mUp);
        mProjection = glm::perspective(glm::radians(mFOV), aspect, mNear, mFar);
        mViewProjection = mProjection * mView;
    }

    void PerspectiveCamera::SetRotation(const glm::vec3 &rotation) {
        mFront = glm::normalize(rotation);

        mRight = glm::normalize(glm::cross(mFront, glm::vec3(0.0f, 1.0f, 0.0f)));
        mUp = glm::normalize(glm::cross(mRight, mFront));
    }

    void PerspectiveCamera::ProcessMouseMovement(float xoffset, float yoffset, float sensitivity, bool constrainPitch) {
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        mYaw += xoffset;
        mPitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch) {
            mPitch = glm::clamp(mPitch, CAMERA_MIN_PITCH, CAMERA_MAX_PITCH);
        }

        RecalculateMatrices();
    }

    void PerspectiveCamera::ProcessKeyboard(MoveDir direction, float deltaTime, float moveSpeed) {
        float velocity = moveSpeed * deltaTime;
        if (direction == FORWARD)
            mPosition += mFront * velocity;
        if (direction == BACKWARD)
            mPosition -= mFront * velocity;
        if (direction == LEFT)
            mPosition -= mRight * velocity;
        if (direction == RIGHT)
            mPosition += mRight * velocity;

        RecalculateMatrices();
    }

    void PerspectiveCamera::ProcessMouseScroll(float yoffset) {
        mFOV -= yoffset;
        mFOV = glm::clamp(mFOV, CAMERA_MIN_ZOOM, CAMERA_MAX_ZOOM);
    }
}
