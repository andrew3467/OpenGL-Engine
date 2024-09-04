//
// Created by Andrew Graser on 9/1/2024.
//

#ifndef NAMECOMPONENT_H
#define NAMECOMPONENT_H


namespace GLE {
    struct NameComponent {
        NameComponent(const std::string &name) : name(name) {}
        NameComponent() : name("Entity") {}
        ~NameComponent() = default;

        std::string name;

        operator const std::string&() const { return name; }
    };
}

#endif //NAMECOMPONENT_H
