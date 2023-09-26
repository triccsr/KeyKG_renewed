//
// Created by triccsr on 9/19/23.
//

#include "RandomDouble.h"


RandomDouble::RandomDouble(double a, double b, uint32_t seedU) {
    uniformRealDistribution=std::uniform_real_distribution<double>(a,b);
    mtGenerator.seed(seedU);
}

double RandomDouble::rand_double() {
    return uniformRealDistribution(mtGenerator);
}
