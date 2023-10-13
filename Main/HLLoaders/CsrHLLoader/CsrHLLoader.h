//
// Created by tricc on 2023/10/13.
//

#ifndef KEYKG_MAIN_HLLOADERS_CSRHLLOADER_CSRHLLOADER_H_
#define KEYKG_MAIN_HLLOADERS_CSRHLLOADER_CSRHLLOADER_H_

#include "AbstractHLLoader.h"
#include "HLType.h"
#include "WeightedGraph.h"
class CsrHLLoader : AbstractHLLoader {
  VType n;
  std::vector<HLType> *hl;
  const WeightedGraph &_ww;
 public:
  double get_dist(int u, int v) override;
  double get_sp(VType u, VType v, std::vector<EType> &edges) override;
  CsrHLLoader()=delete;
  explicit CsrHLLoader(const WeightedGraph &ww,const char *hlFilePath);
  ~CsrHLLoader();
};

#endif //KEYKG_MAIN_HLLOADERS_CSRHLLOADER_CSRHLLOADER_H_
