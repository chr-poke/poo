#include "rngEngine.h"

rngEngine::rngEngine() {
    std::random_device rd;
    rng.seed(rd()); 
}

rngEngine& rngEngine::getInstance() {
    static rngEngine inst;
    return inst;
}

int rngEngine::getRandomInt(const int min, const int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

float rngEngine::getRandomFloat(const float min, const float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}