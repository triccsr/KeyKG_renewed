//
// Created by triccsr on 9/19/23.
//

#ifndef KEYKG_RANDOMDOUBLE_H
#define KEYKG_RANDOMDOUBLE_H


#include <random>
#include <typeinfo>

template <class T>
class RandomMT {
    std::mt19937 mtGenerator;
    std::uniform_real_distribution<double> uniformRealDistribution;
    std::uniform_int_distribution<int> uniformIntDistribution;
public:
    RandomMT()=default;
    RandomMT(T a, T b, uint32_t seedU){
      if(typeid(T)==typeid(double)) {
        uniformRealDistribution = std::uniform_real_distribution<double>(a, b);
      }
      else if(typeid(T)==typeid(int)){
        uniformIntDistribution = std::uniform_int_distribution<int>(a,b);
      }
      mtGenerator.seed(seedU);
    }
    T rand_mt() {
      if(typeid(T)==typeid(double)) {
        return uniformRealDistribution(mtGenerator);
      }
      else if(typeid(T)==typeid(int)){
        return uniformIntDistribution(mtGenerator);
      }
    }
};


#endif //KEYKG_RANDOMDOUBLE_H
