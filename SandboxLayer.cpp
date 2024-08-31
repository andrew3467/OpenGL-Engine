//
// Created by Andrew Graser on 7/26/2024.
//

#include "SandboxLayer.h"

#include "Core/Application.h"
#include "Core/CameraController.h"
#include "Core/Log.h"
#include "Core/Input.h"
#include "Core/Util/Random.h"
#include "Core/Transform.h"
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

GLE::Transform RandomPosition() {
    const float min = -10.0f, max = 10.0f;

    return {
        RandomVec3(min, max),
        RandomVec3(min, max),
        RandomVec3(0.2, 1),
    };
}


std::vector<GLE::Transform> sTransforms;


SandboxLayer::SandboxLayer() : GLE::Layer("Sandbox Layer") {

}

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
        sTransforms.push_back(RandomPosition());
    }
}

void SandboxLayer::OnRender() {
    GLE::Renderer::StartScene(*mCamera);

    for(auto& transform : sTransforms) {
        GLE::Renderer::SubmitPrimitive(GLE::PrimitiveType::Cube, *StandardShader, transform);
    }

    GLE::Renderer::RenderScene();
}

void SandboxLayer::OnEvent(Event &e) {
    Layer::OnEvent(e);
}
