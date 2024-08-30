//
// Created by Andrew Graser on 7/26/2024.
//

#include "SandboxLayer.h"

#include "Core/Log.h"
#include "Core/Input.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

#include "glm/gtx/string_cast.hpp"
#include "GLFW/glfw3.h"



std::shared_ptr<GLE::Shader> StandardShader;

SandboxLayer::SandboxLayer() : GLE::Layer("Sandbox Layer") {

}

void SandboxLayer::OnCreate() {
    GLE_INFO("Created Layer: {0}", mName);
}

void SandboxLayer::OnRun() {
    mCamera = GLE::PerspectiveCamera::Create({0,0,6});

    StandardShader = GLE::Shader::Create("../assets/shaders/Standard.glsl");
}

void SandboxLayer::OnUpdate(const float dt) {

    const float moveSpeed = 5.0f;
    if(GLE::Input::GetKey(GLFW_KEY_W)) {
        mCamera->ProcessKeyboard(GLE::MoveDir::FORWARD, dt, moveSpeed);
    }
    if(GLE::Input::GetKey(GLFW_KEY_S)) {
        mCamera->ProcessKeyboard(GLE::MoveDir::BACKWARD, dt, moveSpeed);
    }
    if(GLE::Input::GetKey(GLFW_KEY_A)) {
        mCamera->ProcessKeyboard(GLE::MoveDir::LEFT, dt, moveSpeed);
    }
    if(GLE::Input::GetKey(GLFW_KEY_D)) {
        mCamera->ProcessKeyboard(GLE::MoveDir::RIGHT, dt, moveSpeed);
    }

    static uint32_t prevX = 0, prevY = 0;
    static bool firstMouse = true;
    static bool firstScrollDown = true;

    if(GLE::Input::GetMouseButton(GLFW_MOUSE_BUTTON_MIDDLE)) {
        auto [x,y] = GLE::Input::GetMousePosition();
        if(firstMouse) {
            prevX = x;
            prevY = y;
            firstMouse = false;
        }

        if (firstScrollDown) {
            GLE::Input::SetMousePosition(prevX, prevY);
            firstScrollDown = false;
        }

        float xOffset = x - prevX;
        float yOffset = prevY - y;

        const float sensitivity = 2.f;
        mCamera->ProcessMouseMovement(xOffset, yOffset, sensitivity * dt);
        prevX = x;
        prevY = y;
    }else {
        firstScrollDown = true;
    }

}

void SandboxLayer::OnRender() {
    GLE::Renderer::StartScene(*mCamera);

    GLE::Renderer::SubmitPrimitive(GLE::PrimitiveType::Cube, *StandardShader);

    GLE::Renderer::RenderScene();
}

void SandboxLayer::OnEvent(Event &e) {
    Layer::OnEvent(e);
}
