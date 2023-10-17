//
// Created by triccsr on 10/7/23.
//

#ifndef KEYKG_HUBLABEL_HLTYPE_H_
#define KEYKG_HUBLABEL_HLTYPE_H_
#include "GraphTypes.h"
class HLType {
  VType _label{-1};
  VType _prevEdge{-1}; //the previous edge index of the path from label to current
  double _dist{1e16}; //the distance from label to current
 public:
  HLType() = default;
  HLType(VType label, VType prevEdge, double dist) : _label(label), _prevEdge(prevEdge), _dist(dist) {}
  VType label() const { return _label; }
  VType previous_edge() const { return _prevEdge; }
  double dist() const { return _dist; }
  bool operator < (const HLType &hl)const{
    return _label<hl._label;
  }
};
#endif //KEYKG_HUBLABEL_HLTYPE_H_