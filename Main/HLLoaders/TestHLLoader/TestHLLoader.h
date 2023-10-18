//
// Created by tricc on 2023/10/13.
//

#ifndef KEYKG_MAIN_HLLOADERS_TESTHLLOADER_TESTHLLOADER_H_
#define KEYKG_MAIN_HLLOADERS_TESTHLLOADER_TESTHLLOADER_H_

#include "AbstractHLLoader.h"
#include "WeightedGraph.h"

class TestHLLoader: AbstractHLLoader{
  const WeightedGraph &_ww;
 public:
  double get_dist(VType u, VType v)const override;
  double get_sp(VType u, VType v, std::vector<EType> &edges)const override;
  void get_sp_with_label(VType u, HLType uHL, VType v, HLType vHL, std::vector<EType> &edges)const override {};
  void insert_into_dhl(VType v, ArrayOnHeap<DhlType> &dhl)const override{};
  void erase_from_dhl(VType v, ArrayOnHeap<DhlType> &dhl) const override{};
  std::pair<HLType, DhlType> get_min_dhl(VType v, ArrayOnHeap<DhlType> &dhl) const override{};
  TestHLLoader()=delete;
  explicit TestHLLoader(const WeightedGraph &ww);
};

#endif //KEYKG_MAIN_HLLOADERS_TESTHLLOADER_TESTHLLOADER_H_
