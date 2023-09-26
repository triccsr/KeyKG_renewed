//
// Created by triccsr on 9/25/23.
//

#ifndef KEYKG_BC_H
#define KEYKG_BC_H

#include <cstdint>
#include "WeightedGraph.h"

class BC{
    uint64_t *spCount;
    double *delta;
    double *dis;
    bool *ok;

    const WeightedGraph &ww;
    double *bc;
    const double eps=1e-6;
    const double doubleINF=1e16; //
    void add_delta_from(int src);


public:
    BC()=delete;
    ~BC();
    BC(const WeightedGraph &argWW, int pivotNum);
    double get_BC_of(VType ver);
};

#endif //KEYKG_BC_H
