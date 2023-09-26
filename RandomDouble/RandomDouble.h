//
// Created by triccsr on 9/19/23.
//

#ifndef KEYKG_RANDOMDOUBLE_H
#define KEYKG_RANDOMDOUBLE_H


#include <random>

class RandomDouble {
    std::mt19937 mtGenerator;
    std::uniform_real_distribution<double> uniformRealDistribution;
public:
    RandomDouble()=default;
    RandomDouble(double a,double b,uint32_t seedU);
    double rand_double();
};


#endif //KEYKG_RANDOMDOUBLE_H
