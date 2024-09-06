//
// Created by Andrew Graser on 8/27/2024.
//

#ifndef OPENGL_ENGINE_CAMERA_H
#define OPENGL_ENGINE_CAMERA_H

#include <glm/glm.hpp>

namespace GLE {
    enum MoveDir {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    class Camera {
    public:
        static std::shared_ptr<Camera> Create(const glm::vec3& position) {return std::make_shared<Camera>(position);}

        Camera();

        Camera(const glm::vec3 &position);

        ~Camera();

        void SetPosition(const glm::vec3 &position) {
            mPosition = position;
            RecalculateMatrices();
        }

        void SetRotation(const glm::vec3 &rotation);

        void ProcessKeyboard(MoveDir direction, float deltaTime, float moveSpeed);

        void ProcessMouseMovement(float xoffset, float yoffset, float sensitivity, bool constrainPitch = true);

        void ProcessMouseScroll(float yoffset);

        const glm::mat4 &GetViewProjection() const { return mViewProjection; }
        const glm::mat4 &GetView() const { return mView; }
        const glm::mat4 &GetProjection() const { return mProjection; }

        const glm::vec3 &GetPosition() const { return mPosition; }

    private:
        void RecalculateMatrices();

    private:
        glm::mat4 mView;
        glm::mat4 mProjection;
        glm::mat4 mViewProjection;

        glm::vec3 mPosition;
        glm::vec3 mFront = {0.0f, 0.0f, 1.0f};
        glm::vec3 mUp = {0.0f, 1.0f, 0.0f};
        glm::vec3 mRight = {1.0f, 0.0f, 0.0f};
        glm::vec3 mWorldUp = {0.0f, 1.0f, 0.0f};

        float mFOV = 60.0f;
        float mNear = 0.1f, mFar = 100.0f;

        float mYaw = -90.0f;
        float mPitch = 0.0f;
    };
}


#endif //OPENGL_ENGINE_CAMERA_H
