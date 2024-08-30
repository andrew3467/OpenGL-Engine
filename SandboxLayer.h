//
// Created by Andrew Graser on 7/26/2024.
//

#ifndef OPENGL_ENGINE_SANDBOXLAYER_H
#define OPENGL_ENGINE_SANDBOXLAYER_H


#include "Core/Layer.h"
#include "Renderer/Camera.h"

class SandboxLayer : public GLE::Layer {
public:
    SandboxLayer();
    ~SandboxLayer() = default;


public:
    void OnEvent(Event &e) override;

    void OnCreate() override;
    void OnRun() override;
    void OnUpdate(float dt) override;
    void OnRender() override;

private:
    std::shared_ptr<GLE::PerspectiveCamera> mCamera;
};


#endif //OPENGL_ENGINE_SANDBOXLAYER_H
