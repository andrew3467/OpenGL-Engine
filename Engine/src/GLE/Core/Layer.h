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
        virtual void OnRun() {}


        virtual void OnStart() {}
        virtual void OnUpdate(float dt) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
        virtual void OnDestroy() {}


        const std::string &GetName() const {return mName;}


    protected:
        std::string mName;
    };
}


#endif //OPENGL_ENGINE_LAYER_H
