//
// Created by tricc on 2023/10/13.
//

#include <cassert>
#include "TestHLLoader.h"
double TestHLLoader::get_dist(VType u, VType v) {
  return 0;
}
double TestHLLoader::get_sp(VType u, VType v, std::vector<EType> &edges) {
  return 0;
}
TestHLLoader::TestHLLoader(const WeightedGraph &ww):_ww(ww){
  assert(ww.vertex_count()<=10000);
}
