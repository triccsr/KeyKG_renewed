//
// Created by tricc on 2023/10/12.
//

#ifndef KEYKG_HUBLABELGENERATOR_DIJKSTRABASED_DIJKSTRABASEDABSTRACT_H_
#define KEYKG_HUBLABELGENERATOR_DIJKSTRABASED_DIJKSTRABASEDABSTRACT_H_

#include <cstdio>
#include <vector>
#include <set>
#include "HubLabelGeneratorAbstract.h"
#include "WeightedGraphDef.h"
#include "WeightedGraph.h"

 class DijkstraBasedAbstract : public HubLabelGeneratorAbstract{
 private:
  class HLType {
    VType _label;
    VType _prevEdge; //the previous edge index of the path from label to current
    double _dist; //the distance from label to current
   public:
    HLType() = delete;
    HLType(VType label, VType prevEdge, double dist) : _label(label), _prevEdge(prevEdge), _dist(dist) {}
    VType label() const { return _label; }
    VType previous_edge() const { return _prevEdge; }
    double dist() const { return _dist; }
    bool operator < (const HLType &hl)const{
      return _label<hl._label;
    }
  };
  std::set<HLType> *L{nullptr};
  void write_hub_label2file(const char *dstFilePath);
  void dijkstra_in_order(const std::vector<VType> &orderedVertices);
  double get_dist(VType u, VType v, const std::set<HLType> &uHL, const std::set<HLType> &vHL) const;
 protected:
  WeightedGraph ww;
  const double doubleINF=1e16;
  virtual std::vector<VType> get_ordered_vertices()=0;
 public:
  void gen_hub_label_file(const char* dstPath,const char *wgFilePath) override;
  DijkstraBasedAbstract()=default;
};

#endif //KEYKG_HUBLABELGENERATOR_DIJKSTRABASED_DIJKSTRABASEDABSTRACT_H_
