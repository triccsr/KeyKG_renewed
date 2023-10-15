//
// Created by tricc on 2023/10/13.
//

#ifndef KEYKG_MAIN_HUBLABELGENERATOR_DIJKSTRABASED_SHL_SHL_H_
#define KEYKG_MAIN_HUBLABELGENERATOR_DIJKSTRABASED_SHL_SHL_H_

#include "DijkstraBasedAbstract.h"

class SHL : public DijkstraBasedAbstract{
 private:
  VType _pivotNum{};
  std::vector<VType> get_ordered_vertices() override;
 public:
  SHL()=delete;
  explicit SHL(VType pivotNum): _pivotNum(pivotNum){}
};

#endif //KEYKG_MAIN_HUBLABELGENERATOR_DIJKSTRABASED_SHL_SHL_H_
