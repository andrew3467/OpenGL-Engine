//
// Created by Andrew Graser on 8/31/2024.
//

#ifndef RANDOM_H
#define RANDOM_H

#include <random>


namespace GLE {
    class Random {
    public:
        Random() : Random(52312) {}
        Random(int seed);
        ~Random() = default;

        int Range(int a, int b);
        float Range(float a, float b);

    private:
        std::random_device mRandomDevice;
        std::mt19937_64  mEngine;
    };
}



#endif //RANDOM_H
