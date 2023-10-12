//
// Created by tricc on 2023/10/12.
//

#ifndef KEYKG_HUBLABELGENERATOR_DIJKSTRABASED_DIJKSTRABASEDABSTRACT_H_
#define KEYKG_HUBLABELGENERATOR_DIJKSTRABASED_DIJKSTRABASEDABSTRACT_H_

#include <cstdio>
#include <vector>
#include "HubLabelGeneratorAbstract.h"
#include "WeightedGraphDef.h"

class DijkstraBasedAbstract : HubLabelGeneratorAbstract{
 protected:
  virtual void write_hub_label(FILE* hlFile,FILE* wgFile)=0;
  void dijkstra_in_order(const std::vector<VType> &orderedVertices);
 public:
  void gen_hub_label_file(const char* dstPath,const char *wgFilePath) override;
};

#endif //KEYKG_HUBLABELGENERATOR_DIJKSTRABASED_DIJKSTRABASEDABSTRACT_H_
