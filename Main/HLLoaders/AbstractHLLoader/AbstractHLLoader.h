//
// Created by tricc on 2023/10/13.
//

#ifndef KEYKG_MAIN_HLLOADERS_ABSTRACTHLLOADER_ABSTRACTHLLOADER_H_
#define KEYKG_MAIN_HLLOADERS_ABSTRACTHLLOADER_ABSTRACTHLLOADER_H_

#include <vector>
#include "WeightedGraphDef.h"
class AbstractHLLoader {
 public:
  virtual double get_dist(VType u,VType v)=0;
  virtual double get_sp(VType u,VType v, std::vector<EType> &edges)=0;
};

#endif //KEYKG_MAIN_HLLOADERS_ABSTRACTHLLOADER_ABSTRACTHLLOADER_H_
