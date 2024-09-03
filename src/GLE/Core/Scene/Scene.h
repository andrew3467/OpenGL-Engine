//
// Created by Andrew Graser on 9/2/2024.
//

#ifndef SCENE_H
#define SCENE_H

#include <entt/entt.hpp>

#include "ECS/Entity.h"


namespace GLE {
    class UUID;

    class Scene {
        public:
        Scene();
        ~Scene();


        Entity CreateEntity(const std::string& name = std::string());
        Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());



    private:
        entt::registry mRegistry;


        friend class Entity;
    };
}



#endif //SCENE_H
