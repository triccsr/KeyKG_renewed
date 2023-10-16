//
// Created by triccsr on 9/16/23.
//

#ifndef KEYKG_WEIGHTEDOUTEDGE_H
#define KEYKG_WEIGHTEDOUTEDGE_H

#include "../GraphTypes/GraphTypes.h"
#include <cstdint>

class WeightedOutEdge {
    VType _to{};
    double _weight{};
    EType _edgeIndex{};
public:
    WeightedOutEdge()=default;
    WeightedOutEdge(VType to,double weight,EType edgeIndex);
    double weight() const;
    VType to() const;
    EType edge_index() const;

};




#endif //KEYKG_WEIGHTEDOUTEDGE_H
