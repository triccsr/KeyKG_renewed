//
// Created by tricc on 2023/10/16.
//

#ifndef KEYKG_MAIN_DHLTYPE_DHLTYPE_H_
#define KEYKG_MAIN_DHLTYPE_DHLTYPE_H_
class DhlType{
  VType _vIndex;
  double _dist;
 public:
  DhlType()=default;
  explicit DhlType(VType vIndex,double dist):_vIndex(vIndex),_dist(dist){}
  VType vertex_index(){return _vIndex;}
  double dist(){return _dist;}
};

#endif //KEYKG_MAIN_DHLTYPE_DHLTYPE_H_
