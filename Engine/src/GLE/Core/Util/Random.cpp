//
// Created by Andrew Graser on 8/31/2024.
//

#include "Random.h"

#include <random>

namespace GLE {
    Random::Random(int seed)
        : mEngine(seed)
    {
    }

    int Random::Range(int a, int b) {
        std::uniform_int_distribution distribution(a, b);
        return distribution(mEngine);
    }

    float Random::Range(float a, float b) {
        std::uniform_real_distribution distribution(a, b);
        return distribution(mEngine);
    }
}
