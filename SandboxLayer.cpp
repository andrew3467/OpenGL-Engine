//
// Created by Andrew Graser on 7/26/2024.
//

#include "SandboxLayer.h"

#include "Core/Log.h"


#include "Renderer/Renderer.h"

SandboxLayer::SandboxLayer() : GLE::Layer("Sandbox Layer") {

}

void SandboxLayer::OnCreate() {
    GLE_INFO("Created Layer: {0}", mName);
}

void SandboxLayer::OnUpdate() {

}

void SandboxLayer::OnRender() {
    GLE::Renderer::StartScene();

    GLE::Renderer::SubmitPrimitive(GLE::PrimitiveType::Square);

    GLE::Renderer::RenderScene();
}

void SandboxLayer::OnEvent(Event &e) {
    Layer::OnEvent(e);
}
