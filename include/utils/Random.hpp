//
// Created by Seres67 on 24/10/2022.
//

#ifndef WAVEFUNCTIONCOLLAPSE_RANDOM_HPP
#define WAVEFUNCTIONCOLLAPSE_RANDOM_HPP

#include <random>

class Random
{
public:
    static void initialize(int max_states);

    static int getRandomInt(int min, int max);

private:
    static std::mt19937 m_generator;
    static std::uniform_int_distribution<int> m_distribution;
};

#endif //WAVEFUNCTIONCOLLAPSE_RANDOM_HPP
