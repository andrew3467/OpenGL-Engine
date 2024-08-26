//
// Created by Andrew Graser on 7/26/2024.
//

#ifndef OPENGL_ENGINE_SANDBOXLAYER_H
#define OPENGL_ENGINE_SANDBOXLAYER_H


#include "Core/Layer.h"

class SandboxLayer : public GLE::Layer {
public:
    SandboxLayer();
    ~SandboxLayer() = default;


public:
    void OnEvent(Event &e) override;

    void OnCreate() override;
    void OnUpdate() override;
    void OnRender() override;
};


#endif //OPENGL_ENGINE_SANDBOXLAYER_H
