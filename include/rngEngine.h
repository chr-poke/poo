#pragma once
#include <random>
#include <stdexcept>

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

    template <typename T>
    T pickRandom(const std::vector<T>& list) {
        if (list.empty())
            throw std::runtime_error("Cannot pick from an empty list!");
        int index = getRandomInt(0, list.size() - 1);
        return list[index];
    }
};
