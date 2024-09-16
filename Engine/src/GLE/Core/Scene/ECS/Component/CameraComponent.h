//
// Created by Andrew Graser on 9/13/2024.
//


#pragma once

#include "Renderer/Camera.h"

namespace GLE {
    struct CameraComponent {
        CameraComponent(std::shared_ptr<Camera> camera) : Camera(std::move(camera)) {}
        CameraComponent() : Camera(Camera::Create(glm::vec3(0))) {}
        CameraComponent(const CameraComponent&) = default;
        ~CameraComponent() = default;


        std::shared_ptr<Camera> Camera;
    };
}
