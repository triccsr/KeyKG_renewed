//
// Created by tricc on 2023/10/16.
//

#ifndef KEYKG_MAIN_DHLTYPE_DHLTYPE_H_
#define KEYKG_MAIN_DHLTYPE_DHLTYPE_H_
#include "HLType.h"
class DhlType{
  VType _minVertexIndex{-1};
  HLType _minHL;
 public:
  DhlType()=default;
  explicit DhlType(VType vIndex,HLType hl):_minVertexIndex(vIndex),_minHL(hl){}
  VType min_vertex_index() const{return _minVertexIndex;}
  HLType min_hl() const{return _minHL;}
};

#endif //KEYKG_MAIN_DHLTYPE_DHLTYPE_H_
