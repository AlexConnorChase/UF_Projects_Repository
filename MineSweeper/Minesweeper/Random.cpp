//
// Created by Alex Chase on 12/7/20.
//

#include "Random.h"
#include <ctime>

std::mt19937 Random::random(time(0));

int Random::Number(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(random);
}
float Random::Float(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(random);
}