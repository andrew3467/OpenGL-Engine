//
// Created by Andrew Graser on 7/26/2024.
//

#include "SandboxLayer.h"

#include "Core/Log.h"

SandboxLayer::SandboxLayer() : GLE::Layer("Sandbox Layer") {

}

void SandboxLayer::OnCreate() {
    GLE_INFO("Created Layer: {0}", mName);
}

void SandboxLayer::OnUpdate() {

}

void SandboxLayer::OnRender() {

}

void SandboxLayer::OnEvent(Event &e) {
    Layer::OnEvent(e);
}
