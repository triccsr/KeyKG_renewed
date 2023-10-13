//
// Created by tricc on 2023/10/13.
//
#include <algorithm>
#include "SHL.h"
#include "BC.h"
std::vector<VType> SHL::get_ordered_vertices() {
  BC bc(ww,_pivotNum);
  std::vector<VType> vertices(static_cast<unsigned long long int>(ww.vertex_count()));
  for(VType v=0;v<ww.vertex_count();++v){
    vertices.at(v)=v;
  }
  std::sort(vertices.begin(),vertices.end(),[&bc](VType a,VType b){return bc.get_BC_of(a)>bc.get_BC_of(b);});
  return vertices;
}
