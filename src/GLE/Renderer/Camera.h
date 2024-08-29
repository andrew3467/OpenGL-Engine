//
// Created by Andrew Graser on 8/27/2024.
//

#ifndef OPENGL_ENGINE_CAMERA_H
#define OPENGL_ENGINE_CAMERA_H

#include <glm/glm.hpp>

namespace GLE {
    enum class MoveDir {
        Forward = 0,
        Backward = 1,
        Right = 2,
        Left = 3,
    };

    class Camera {
    public:
        inline static std::shared_ptr<Camera> Create(const glm::vec3& position) {return std::make_shared<Camera>(position);}

        Camera(const glm::vec3& position);
        ~Camera();


        glm::mat4 Projection() {return mProjection;}
        glm::mat4 View() {return mView;}
        glm::mat4 ViewProj() {return mViewProj;}

        void Move(MoveDir dir, float val);
        void Rotate(float yawOffset, float pitchOffset);

    private:
        void RecalculateMatrices();


    private:
        glm::mat4 mView, mProjection, mViewProj;

        glm::vec3 mPosition = {0,0,0};

        float mFOV = 45.0f;
        float mNear = 0.1f, mFar = 100.0f;

        glm::vec3 mUp = {0,1,0};
        glm::vec3 mFront = {0, 0, 1};
        glm::vec3 mRight = {-1,0,0};

        float mYaw = -90.0f;
        float mPitch = 0.0f;
    };
}


#endif //OPENGL_ENGINE_CAMERA_H
