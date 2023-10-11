//
// Created by tricc on 2023/10/11.
//

#ifndef KEYKG_MAIN_WEIGHTEDGRAPH_WEIGHTEDEDGE_H_
#define KEYKG_MAIN_WEIGHTEDGRAPH_WEIGHTEDEDGE_H_
#include "WeightedGraphDef.h"
class WeightedEdge{
  EType _edgeIndex;
  VType _u,_v;
  double _weight;
 public:
  WeightedEdge()=default;
  WeightedEdge(EType edgeIndex,VType u,VType v,double weight):
  _edgeIndex(edgeIndex),_u(u),_v(v),_weight(weight){}
  EType edge_index(){return _edgeIndex;}
  VType u(){return _u;}
  VType v(){return _v;}
  double weight(){return _weight;}
};
#endif //KEYKG_MAIN_WEIGHTEDGRAPH_WEIGHTEDEDGE_H_
