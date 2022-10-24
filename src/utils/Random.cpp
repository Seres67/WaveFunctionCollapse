//
// Created by Seres67 on 24/10/2022.
//

#include <utils/Random.hpp>

std::mt19937 Random::m_generator;
std::uniform_int_distribution<int> Random::m_distribution;

void Random::initialize(int max_states)
{
    std::random_device rd;
    m_generator = std::mt19937(rd());
}

int Random::getRandomInt(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(m_generator);
}