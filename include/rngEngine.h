#pragma once
#include <random>

class rngEngine {
private:
    std::mt19937 rng;
    rngEngine();

public:
    rngEngine(const rngEngine&) = delete;
    rngEngine& operator=(const rngEngine&) = delete;
    static rngEngine& getInstance();

    int getRandomInt(int min, int max);
    float getRandomFloat(float min, float max);
};