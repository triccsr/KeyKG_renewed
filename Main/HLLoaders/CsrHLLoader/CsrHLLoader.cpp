//
// Created by tricc on 2023/10/13.
//

#include <cstdio>
#include <cassert>
#include "CsrHLLoader.h"
#include "OpenFile.h"
double CsrHLLoader::get_dist(int u, int v) const{
  double minDist=1e16;
  for(size_t i=0,j=0;i<hl[u].size();++i){
    while(j<hl[v].size()&&hl[v][j].label()<hl[u][i].label()){
      ++j;
    }
    if(j==hl[v].size())break;
    if(hl[u][i].label()==hl[v][j].label()){
      minDist=std::min(minDist,hl[u][i].dist()+hl[v][j].dist());
    }
  }
  return minDist;
}

double CsrHLLoader::get_sp(VType u, VType v, std::vector<EType> &edges) const{
  if(u==v){
    //edges.clear();
    return 0.0;
  }
  double minDist=1e16;
  VType center=-1;
  HLType uHL(-1,-1,1e16),vHL(-1,-1,1e16);
  for(size_t i=0,j=0;i<hl[u].size()&&j<hl[v].size();++i){
    while(j<hl[v].size()&&hl[v][j].label()<hl[u][i].label()){
      ++j;
    }
    if(j==hl[v].size())break;
    if(hl[u][i].label()==hl[v][j].label()){
      double tmpDist=hl[u][i].dist()+hl[v][j].dist();
      if(tmpDist<minDist){
        minDist=tmpDist;
        center=hl[u][i].label();
        uHL=hl[u][i];
        vHL=hl[v][j];
      }
    }
  }
  if(center==-1)
    return minDist;
  get_sp_with_label(u,uHL,v,vHL,edges);
  return minDist;
}

void CsrHLLoader::get_path_to_label(VType u, HLType uHL, std::vector<EType> &edges) const{
  VType center=uHL.label();
  while(uHL.previous_edge()!=-1){
    edges.push_back(uHL.previous_edge());
    u=_ww.get_the_other_endpoint(u,uHL.previous_edge());
    if(u==center){
      break;
    }
    uHL=*std::lower_bound(hl[u].begin(),hl[u].end(),HLType(center,0,0));;
  }
}

void CsrHLLoader::get_sp_with_label(VType u, HLType uHL, VType v, HLType vHL, std::vector<EType> &edges) const{
  //edges.clear();
  get_path_to_label(u,uHL,edges);
  get_path_to_label(v,vHL,edges);
}

CsrHLLoader::CsrHLLoader(const WeightedGraph &ww,const char *hlFilePath):_ww(ww){
  FILE* hlFile=OpenFile::open_r(hlFilePath);
  fscanf(hlFile,"%d",&n);
  hl=new ArrayOnHeap<HLType> [n];
  for(VType v=0;v<n;++v){
    size_t sz;
    fscanf(hlFile,"%zu",&sz);
    hl[v].resize(sz);
    for(size_t i=0;i<sz;++i){
      VType label;
      EType prevEdge;
      double d;
      fscanf(hlFile,"%d%d%lf",&label,&prevEdge,&d);
      hl[v].at(i)=HLType(label,prevEdge,d);
    }
  }
}
CsrHLLoader::~CsrHLLoader() {
  delete[] hl;
}
void CsrHLLoader::insert_into_dhl(VType v, ArrayOnHeap<DhlType> &dhl) const {
  for(VType i=0;i<static_cast<VType>(hl[v].size());++i){
    size_t label= static_cast<size_t>(hl[v][i].label());
    if(hl[v][i].dist() < dhl[label].min_hl().dist()){
      dhl[label]= DhlType(v,hl[v][i]);
    }
  }
}
std::pair<HLType,DhlType> CsrHLLoader::get_min_dhl(VType v, ArrayOnHeap<DhlType> &dhl) const {
  double minDist=1e16;
  std::pair<HLType,DhlType> res;
  for(VType i=0;i<static_cast<VType>(hl[v].size());++i){
    double currDist=hl[v][i].dist()+dhl[static_cast<size_t>(hl[v][i].label())].min_hl().dist();
    if(currDist<minDist){
      minDist=currDist;
      res.first=hl[v][i];
      res.second=dhl[static_cast<size_t>(hl[v][i].label())];
    }
  }
  return res;
}
void CsrHLLoader::erase_from_dhl(VType v, ArrayOnHeap<DhlType> &dhl) const {
  for(VType i=0;i<static_cast<VType>(hl[v].size());++i) {
    size_t label = static_cast<size_t>(hl[v][i].label());
    dhl[label] = DhlType();
  }
}





