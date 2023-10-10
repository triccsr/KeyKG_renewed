//
// Created by triccsr on 9/16/23.
//
#include "WeightedOutEdge.h"

WeightedOutEdge::WeightedOutEdge(VType tmpTo, double tmpWeight,EType tmpEdgeIndex) : _to(tmpTo), _weight(tmpWeight), _edgeIndex(tmpEdgeIndex) {}

double WeightedOutEdge::weight() const {
    return _weight;
}

VType WeightedOutEdge::to() const {
    return _to;
}

EType WeightedOutEdge::edge_index() const {
    return _edgeIndex;
}
