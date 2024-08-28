//
// Created by Andrew Graser on 8/27/2024.
//

#ifndef OPENGL_ENGINE_CAMERA_H
#define OPENGL_ENGINE_CAMERA_H

#include <glm/glm.hpp>

namespace GLE {
    class Camera {
    public:
        inline static std::shared_ptr<Camera> Create(const glm::vec3& position) {return std::make_shared<Camera>(position);}

        Camera(const glm::vec3& position);
        ~Camera();



    private:
        glm::vec3 mPosition;
        float mRotation;
    };
}


#endif //OPENGL_ENGINE_CAMERA_H
