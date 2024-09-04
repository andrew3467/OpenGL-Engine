//
// Created by Andrew Graser on 9/3/2024.
//

#ifndef IDCOMPONENT_H
#define IDCOMPONENT_H

#include "Core/Util/UUID.h"

namespace GLE {
    struct IDComponent {
        GLE::UUID ID;

        IDComponent(GLE::UUID ID) : ID(ID) {}
        IDComponent() = default;
        IDComponent(const IDComponent&) = default;
        ~IDComponent() = default;
    };
}

#endif //IDCOMPONENT_H
