//
// Created by Andrew Graser on 8/28/2024.
//

#include <random>
#include "Core/Util/UUID.h"


namespace GLE {

    static std::random_device sRandomDevice;
    static std::mt19937_64  sEngine(sRandomDevice());
    static std::uniform_int_distribution<uint64_t> sUniformDistribution;

    UUID::UUID()
        : mUUID(sUniformDistribution(sEngine))
    {

    }

    UUID::UUID(uint64_t uuid)
    : mUUID(uuid)
    {

    }
}