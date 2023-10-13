//
// Created by tricc on 2023/10/13.
//
#include <algorithm>
#include "PLL.h"
std::vector<VType> PLL::get_ordered_vertices() {
  std::vector<VType> vertices;
  vertices.resize(static_cast<unsigned long long int>(ww.vertex_count()));
  for(VType v=0;v<ww.vertex_count();++v){
    vertices.at(v)=v;
  }
  std::sort(vertices.begin(),vertices.end(),[this](VType a,VType b){return ww.out_degree_of(a)>ww.out_degree_of(b);});
  return vertices;
}
