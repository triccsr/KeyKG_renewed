//
// Created by triccsr on 9/16/23.
//

#ifndef KEYKG_WEIGHTEDOUTEDGE_H
#define KEYKG_WEIGHTEDOUTEDGE_H

#include "WeightedGraphDef.h"
#include <cstdint>

class WeightedOutEdge {
    VType to{};
    double weight{};
    EType edgeIndex{};
public:
    WeightedOutEdge()=default;
    WeightedOutEdge(VType to,double weight,EType edgeIndex);
};




#endif //KEYKG_WEIGHTEDOUTEDGE_H
