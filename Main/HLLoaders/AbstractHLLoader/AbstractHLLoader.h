//
// Created by tricc on 2023/10/13.
//

#ifndef KEYKG_MAIN_HLLOADERS_ABSTRACTHLLOADER_ABSTRACTHLLOADER_H_
#define KEYKG_MAIN_HLLOADERS_ABSTRACTHLLOADER_ABSTRACTHLLOADER_H_

#include <vector>
#include "GraphTypes.h"
#include "ArrayOnHeap.h"
#include "DhlType.h"
#include "HLType.h"
class AbstractHLLoader {
 public:
  virtual double get_dist(VType u,VType v)=0;
  virtual double get_sp(VType u,VType v, std::vector<EType> &edges)=0;
  virtual void get_sp_with_label(VType u,HLType uHL,VType v,HLType vHL,std::vector<EType> &edges)=0;
  virtual void insert_into_dhl(VType v, ArrayOnHeap<DhlType> &dhl)=0;
  virtual std::pair<HLType,DhlType> get_min_dhl(VType v, ArrayOnHeap<DhlType> &dhl)=0;
};

#endif //KEYKG_MAIN_HLLOADERS_ABSTRACTHLLOADER_ABSTRACTHLLOADER_H_
