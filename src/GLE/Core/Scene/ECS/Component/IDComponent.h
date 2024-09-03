//
// Created by Andrew Graser on 9/3/2024.
//

#ifndef IDCOMPONENT_H
#define IDCOMPONENT_H

#include "BaseComponent.h"
#include "Core/Util/UUID.h"

namespace GLE {
    struct IDComponent : Component {
        GLE::UUID ID;

        IDComponent() = default;
        IDComponent(const IDComponent&) = default;
    };
}

#endif //IDCOMPONENT_H
