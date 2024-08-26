//
// Created by Andrew Graser on 7/26/2024.
//

#ifndef OPENGL_ENGINE_LAYER_H
#define OPENGL_ENGINE_LAYER_H


#include "Events/Event.h"


namespace GLE {
    class Layer {
    public:
        Layer(const std::string& name = "");

        ~Layer() = default;

        virtual void OnEvent(Event &e) {}

        virtual void OnCreate() {}
        virtual void OnStart() {}
        virtual void OnUpdate() {}
        virtual void OnRender() {}
        virtual void OnDestroy() {}


    protected:
        std::string mName;
    };
}


#endif //OPENGL_ENGINE_LAYER_H
