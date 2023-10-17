//
// Created by tricc on 2023/10/13.
//

#ifndef KEYKG_MAIN_HLLOADERS_CSRHLLOADER_CSRHLLOADER_H_
#define KEYKG_MAIN_HLLOADERS_CSRHLLOADER_CSRHLLOADER_H_

#include "AbstractHLLoader.h"
#include "../../Types/HLType/HLType.h"
#include "WeightedGraph.h"
#include "ArrayOnHeap.h"

class CsrHLLoader : AbstractHLLoader {
  VType n;
  ArrayOnHeap<HLType> *hl;
  const WeightedGraph &_ww;
  void get_path_to_label(VType u,HLType uHL,std::vector<EType> &edges);
 public:
  CsrHLLoader()=delete;
  explicit CsrHLLoader(const WeightedGraph &ww,const char *hlFilePath);
  ~CsrHLLoader();

  double get_dist(int u, int v) override;
  double get_sp(VType u, VType v, std::vector<EType> &edges) override;
  void get_sp_with_label(VType u,HLType uHL,VType v,HLType vHL,std::vector<EType> &edges) override;
  void insert_into_dhl(VType v, ArrayOnHeap<DhlType> &dhl) override;
  std::pair<HLType,DhlType> get_min_dhl(VType v, ArrayOnHeap<DhlType> &dhl) override;
};

#endif //KEYKG_MAIN_HLLOADERS_CSRHLLOADER_CSRHLLOADER_H_
