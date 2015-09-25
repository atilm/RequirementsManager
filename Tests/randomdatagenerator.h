#ifndef RANDOMDATAGENERATOR_H
#define RANDOMDATAGENERATOR_H

#include <random>
#include <climits>
#include <QString>

class RandomDataGenerator
{
    std::random_device rd;
    std::mt19937 rng;

public:
    RandomDataGenerator();

    int getInt(int max = INT_MAX, int min = INT_MIN);
    QString getQString(int maxLength = 20, int minLength = 0);
};

#endif // RANDOMDATAGENERATOR_H
