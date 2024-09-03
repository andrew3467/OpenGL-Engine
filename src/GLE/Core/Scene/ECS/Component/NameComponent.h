//
// Created by Andrew Graser on 9/1/2024.
//

#ifndef NAMECOMPONENT_H
#define NAMECOMPONENT_H
#include <string>

#include "BaseComponent.h"


namespace GLE {
    struct NameComponent : BaseComponent {
        NameComponent(const std::string &name) : name(name) {}
        NameComponent() : name("Entity") {}

        std::string name;

        operator const std::string&() const { return name; }
    };
}

#endif //NAMECOMPONENT_H
