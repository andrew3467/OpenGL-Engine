//
// Created by apgra on 9/20/2024.
//

#ifndef GLE_LIGHTSYSTEM_H
#define GLE_LIGHTSYSTEM_H


#include "System.h"

namespace GLE
{
    class LightSystem : public System
    {
    public:
        LightSystem(Scene* scene);
        ~LightSystem() override = default;

        LightSystem(const LightSystem &other) = delete;


        virtual void Update() override;
    };
}


#endif //GLE_LIGHTSYSTEM_H
