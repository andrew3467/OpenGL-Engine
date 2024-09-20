//
// Created by apgra on 9/20/2024.
//

#ifndef GLE_RENDERSYSTEM_H
#define GLE_RENDERSYSTEM_H


#include "System.h"

namespace GLE
{
    class RenderSystem : public System
    {
    public:
        RenderSystem(Scene* scene);
        ~RenderSystem() override = default;

        RenderSystem(const RenderSystem &other) = delete;


        virtual void Update() override;
    };
}


#endif //GLE_RENDERSYSTEM_H
