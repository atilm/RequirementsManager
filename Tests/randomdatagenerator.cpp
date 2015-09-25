#include "randomdatagenerator.h"
#include <QByteArray>
#include <iostream>
using namespace std;

RandomDataGenerator::RandomDataGenerator()
{
    rng = std::mt19937(rd());
}

int RandomDataGenerator::getInt(int max, int min)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

QString RandomDataGenerator::getQString(int maxLength, int minLength)
{
    QByteArray characters(
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "/:_ ");

    int length = getInt(maxLength, minLength);

    QString s;

    for(int i=0; i<length; i++){
        int idx = getInt(characters.count()-1, 0);
        s.append(characters.at(idx));
    }

    return s;
}
