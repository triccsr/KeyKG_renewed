//
// Created by tricc on 2023/10/17.
//

#ifndef KEYKG_MAIN_KEYKG_KEYKG_H_
#define KEYKG_MAIN_KEYKG_KEYKG_H_
#include "ArrayOnHeap.h"
#include "DhlType.h"
#include "WeightedGraph.h"
#include "CsrHLLoader.h"
class KeyKG {
  int _g;
  ArrayOnHeap<DhlType> M[10];
  ArrayOnHeap<VType> K[10];
  const WeightedGraph &_ww;
  const CsrHLLoader &_hlLoader;
 public:
  KeyKG()=delete;
  explicit KeyKG(const WeightedGraph &ww,const CsrHLLoader &hlLoader);
  void add_group(size_t groupSize, const VType* indexes);
  void reset_group_number();
  int group_number()const;
  void run(const char *outFile);
};

#endif //KEYKG_MAIN_KEYKG_KEYKG_H_
