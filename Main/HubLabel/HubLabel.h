//
// Created by triccsr on 9/25/23.
//

#ifndef KEYKG_HUBLABEL_H
#define KEYKG_HUBLABEL_H


#include <cstdio>
#include <set>
#include "WeightedGraph.h"
#include "HLType.h"

class HubLabel {
  constexpr static double doubleINF=1e16;
  VType wgVerticesCount;
  size_t hubLabelSize;
  std::vector<HLType> *hubLabelOf;
  static double get_dist(VType u,VType v,std::set<HLType> &uHL,const std::set<HLType> &vHL);
public:
  HubLabel()=default;

  /*
 * Hub label file format:
 * First line an integer n, means that there are n vertices in the graph.
 * For each following ith(0-based) lines:
   * the first size_t number iSize is the size of hub label of vertex i
   * following iSize HLType structs, which are the hub label of i
 */
  explicit HubLabel(FILE* file);
  ~HubLabel();
  static void gen_hub_label_file(const WeightedGraph &ww, int pivotNum);
  size_t hub_label_size()const;
  double get_dist(VType u,VType v);
};


#endif //KEYKG_HUBLABEL_H
