//
// Created by Andrew Graser on 7/26/2024.
//

#include "SandboxLayer.h"

#include "Core/Application.h"
#include "Core/CameraController.h"
#include "Core/Log.h"
#include "Core/Input.h"
#include "Core/Scene/ECS/Entity.h"
#include "Core/Util/Random.h"
#include "Core/Scene/ECS/Component/TransformComponent.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

#include "glm/gtx/string_cast.hpp"
#include "GLFW/glfw3.h"



std::shared_ptr<GLE::Shader> StandardShader;

GLE::CameraController sCameraController;
GLE::Random sRandom(4321312);

glm::vec3 RandomVec3(float min, float max) {
    return {
        sRandom.Range(min, max),
        sRandom.Range(min, max),
        sRandom.Range(min, max)
    };
}

std::vector<GLE::Entity> sEntities;


SandboxLayer::SandboxLayer() : GLE::Layer("Sandbox Layer") {}

void SandboxLayer::OnCreate() {
    GLE_INFO("Created Layer: {0}", mName);
}

void SandboxLayer::OnRun() {
    mCamera = GLE::Camera::Create({0,0,6});
    sCameraController.AddCamera(mCamera);

    StandardShader = GLE::Shader::Create("../assets/shaders/Standard.glsl");
}

void SandboxLayer::OnUpdate(const float dt) {
    sCameraController.Update(dt);

    if(GLE::Input::GetKey(GLFW_KEY_SPACE)) {
        GLE::Entity entity;

    }
}

void SandboxLayer::OnRender() {
    GLE::Renderer::StartScene(*mCamera);

    for(auto& entity : sEntities) {
        //GLE::Renderer::SubmitPrimitive(GLE::PrimitiveType::Cube, *StandardShader, *entity.transform);
    }

    GLE::Renderer::RenderScene();
}

void SandboxLayer::OnEvent(Event &e) {
    Layer::OnEvent(e);
}
