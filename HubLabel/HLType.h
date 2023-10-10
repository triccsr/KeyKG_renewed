//
// Created by triccsr on 10/7/23.
//

#ifndef KEYKG_HUBLABEL_HLTYPE_H_
#define KEYKG_HUBLABEL_HLTYPE_H_
#include "WeightedGraphDef.h"
class HLType {
  VType _label;
  double _dist;
  VType _prev;
 public:
  HLType() = delete;
  HLType(VType label, double dist, VType prev) : _label(label), _dist(dist), _prev(prev) {}
  VType label() const { return _label; }
  double dist() const { return _dist; }
  VType prev() const { return _prev; }
};
#endif //KEYKG_HUBLABEL_HLTYPE_H_