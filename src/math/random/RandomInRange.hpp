#pragma once
#include <random>

int randomInRange(const int min, const int max) {
    static thread_local std::random_device seed;
    static thread_local std::mt19937 gen(seed());
    std::uniform_int_distribution<int> distance(min, max);

    return distance(gen);
}
