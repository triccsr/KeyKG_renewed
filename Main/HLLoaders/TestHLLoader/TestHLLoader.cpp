//
// Created by tricc on 2023/10/13.
//

#include <cassert>
#include <queue>
#include "TestHLLoader.h"
double TestHLLoader::get_dist(VType u, VType v) { //dijkstra
  std::vector<EType> uselessEdges;
  double res=get_sp(u,v,uselessEdges);
  return res;
}
double TestHLLoader::get_sp(VType u, VType v, std::vector<EType> &edges) {
  std::vector<double> dis(static_cast<size_t>(_ww.vertex_count()),1e16);
  std::vector<bool> ok(static_cast<size_t>(_ww.vertex_count()),false);
  std::vector<EType> prevEdge(static_cast<size_t>(_ww.vertex_count()),-1);
  std::priority_queue<std::pair<double,VType>,std::vector<std::pair<double,VType>>,std::greater<std::pair<double,VType> > > pq;
  dis[u]=0.0;
  for(VType loop=0;loop<_ww.vertex_count();++loop){
    while(!pq.empty()&&ok.at(pq.top().second))pq.pop();
    if(pq.empty())break;
    VType cur=pq.top().second;
    pq.pop();
    ok[cur]=true;
    for(WeightedOutEdge outEdge:_ww.out_edges_of(cur)){
      if(dis[cur]+outEdge.weight()<dis[outEdge.to()]){
        dis[outEdge.to()]=dis[cur]+outEdge.weight();
        prevEdge[outEdge.to()]=outEdge.edge_index();
        pq.emplace(dis[outEdge.to()],outEdge.to());
      }
    }
  }
  edges.clear();
  if(!ok.at(v)){
    return dis.at(v);
  }
  VType cur=v;
  while(cur!=u){
    edges.push_back(prevEdge.at(cur));
    cur=_ww.get_the_other_endpoint(cur,prevEdge.at(cur));
  }
  return dis.at(v);
}
TestHLLoader::TestHLLoader(const WeightedGraph &ww):_ww(ww){
  assert(_ww.vertex_count()<=20000);
}
