//
// Created by Andrew Graser on 9/3/2024.
//

#include "Entity.h"





namespace GLE {
    Entity::Entity()
        : mEntityHandle(entt::null), mScene(nullptr)
    {

    }

    Entity::Entity(entt::entity handle, Scene *scene)
        : mEntityHandle(handle), mScene(scene)
    {

    }

    Entity::Entity(const Entity &other)
        : mEntityHandle(other.GetHandle()), mScene(other.GetScene())
    {

    }
}
