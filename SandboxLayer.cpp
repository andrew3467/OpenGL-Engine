//
// Created by Andrew Graser on 7/26/2024.
//

#include "SandboxLayer.h"

#include "Core/Application.h"
#include "Core/CameraController.h"
#include "Core/Log.h"
#include "Core/Input.h"
#include "Core/Scene/ECS/Entity.h"
#include "Core/Scene/ECS/Component/PrimitiveRendererComponent.h"
#include "Core/Util/Random.h"
#include "Core/Scene/ECS/Component/TransformComponent.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

#include "glm/gtx/string_cast.hpp"
#include "GLFW/glfw3.h"



std::shared_ptr<GLE::Shader> StandardShader;

GLE::CameraController sCameraController;

GLE::Scene sScene;


SandboxLayer::SandboxLayer() : GLE::Layer("Sandbox Layer") {}

void SandboxLayer::OnCreate() {
    GLE_INFO("Created Layer: {0}", mName);
}

void SandboxLayer::OnRun() {
    mCamera = GLE::Camera::Create({0,0,6});
    sCameraController.AddCamera(mCamera);

    StandardShader = GLE::Shader::Create("../assets/shaders/Standard.glsl");

    auto entity = sScene.CreateEntity();
    entity.AddComponent<GLE::PrimitiveRendererComponent>().RenderType = GLE::PrimitiveType::Cube;
}

void SandboxLayer::OnUpdate(const float dt) {
    sCameraController.Update(dt);
    sScene.Update(dt);
}

void SandboxLayer::OnRender() {
    GLE::Renderer::StartScene(*mCamera);

    sScene.Render(*StandardShader);

    GLE::Renderer::RenderScene();
}

void SandboxLayer::OnEvent(Event &e) {
    Layer::OnEvent(e);
}
