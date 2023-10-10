//
// Created by triccsr on 10/7/23.
//

#ifndef KEYKG_HUBLABEL_HLTYPE_H_
#define KEYKG_HUBLABEL_HLTYPE_H_
#include "WeightedGraphDef.h"
class HLType {
  VType _label;
  VType _prev; //the previous vertex of the path from label to current
  double _dist; //the distance from label to current
 public:
  HLType() = delete;
  HLType(VType label, VType prev, double dist) : _label(label), _prev(prev), _dist(dist) {}
  VType label() const { return _label; }
  double dist() const { return _dist; }
  VType prev() const { return _prev; }
  bool operator < (const HLType &hl)const{
    return _label<hl._label;
  }
};
#endif //KEYKG_HUBLABEL_HLTYPE_H_