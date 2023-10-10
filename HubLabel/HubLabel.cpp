//
// Created by triccsr on 9/25/23.
//

#include "HubLabel.h"
#include "BC.h"
#include "HLType.h"
#include <algorithm>
void HubLabel::gen_hub_label_file(const WeightedGraph &ww, int pivotNum) {
  BC bc(ww,pivotNum);
  std::vector<std::pair<double,VType>> ss;
  ss.resize(static_cast<unsigned long>(ww.vertex_count()));
  for(VType v=0; v<ww.vertex_count(); ++v){
    auto index=static_cast<unsigned long>(v);
    ss[index].first=bc.get_BC_of(v);
    ss[index].second=v;
  }
  std::sort(ss.begin(),ss.end(),std::greater<std::pair<double,VType>>());

  std::vector<bool> visited(static_cast<size_t>(ww.vertex_count()),false);
  std::vector<double> d(static_cast<size_t>(ww.vertex_count()),doubleINF);
  auto *labels=new std::vector<HLType>[ww.vertex_count()];

  for(auto & s : ss){
    VType v=s.second;
    std::vector<VType> allVisited;
    std::vector<VType> needUpdate;
    d[v]=0.0;

  }
}
void HubLabel::load_hub_label_file(FILE *file) {

}
