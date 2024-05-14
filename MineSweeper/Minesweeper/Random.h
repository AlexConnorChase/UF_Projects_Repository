//
// Created by Alex Chase on 12/7/20.
//
#pragma once
#include <random>
using namespace std;

class Random {
    static std::mt19937 random;
public:
    static int Number(int min, int max);
    static float Float(float min, float max);
};



