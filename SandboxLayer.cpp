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
    mCamera = GLE::Camera::Create({0,0, -6});

    StandardShader = GLE::Shader::Create("../assets/shaders/Standard.glsl");
}

void SandboxLayer::OnUpdate(float dt) {

    const float moveSpeed = 5.0f;
    if(GLE::Input::GetKey(GLFW_KEY_W)) {
        mCamera->Move(GLE::MoveDir::Forward, dt * moveSpeed);
    }
    if(GLE::Input::GetKey(GLFW_KEY_S)) {
        mCamera->Move(GLE::MoveDir::Backward, dt * moveSpeed);
    }
    if(GLE::Input::GetKey(GLFW_KEY_A)) {
        mCamera->Move(GLE::MoveDir::Left, dt * moveSpeed);
    }
    if(GLE::Input::GetKey(GLFW_KEY_D)) {
        mCamera->Move(GLE::MoveDir::Right, dt * moveSpeed);
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
