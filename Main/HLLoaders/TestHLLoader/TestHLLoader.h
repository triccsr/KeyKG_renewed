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
  double get_dist(VType u, VType v) override;
  double get_sp(VType u, VType v, std::vector<EType> &edges) override;
  TestHLLoader()=delete;
  explicit TestHLLoader(const WeightedGraph &ww);
};

#endif //KEYKG_MAIN_HLLOADERS_TESTHLLOADER_TESTHLLOADER_H_
