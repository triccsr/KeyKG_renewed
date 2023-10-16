//
// Created by tricc on 2023/10/13.
//

#ifndef KEYKG_MAIN_HLLOADERS_CSRHLLOADER_CSRHLLOADER_H_
#define KEYKG_MAIN_HLLOADERS_CSRHLLOADER_CSRHLLOADER_H_

#include "AbstractHLLoader.h"
#include "HLType.h"
#include "WeightedGraph.h"
#include "ArrayOnHeap.h"

class CsrHLLoader : AbstractHLLoader {
  VType n;
  ArrayOnHeap<HLType> *hl;
  const WeightedGraph &_ww;
 public:
  CsrHLLoader()=delete;
  explicit CsrHLLoader(const WeightedGraph &ww,const char *hlFilePath);
  ~CsrHLLoader();

  double get_dist(int u, int v) override;
  double get_sp(VType u, VType v, std::vector<EType> &edges) override;

  void insert_into_dhl(VType v, ArrayOnHeap<DhlType> &dhl) override;
  void distance2dhl(VType v, ArrayOnHeap<DhlType> &dhl) override;
};

#endif //KEYKG_MAIN_HLLOADERS_CSRHLLOADER_CSRHLLOADER_H_
