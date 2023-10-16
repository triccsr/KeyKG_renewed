//
// Created by tricc on 2023/10/13.
//

#include <cstdio>
#include <cassert>
#include "CsrHLLoader.h"
#include "OpenFile.h"
double CsrHLLoader::get_dist(int u, int v) {
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

double CsrHLLoader::get_sp(VType u, VType v, std::vector<EType> &edges) {
  if(u==v){
    edges.clear();
    return 0.0;
  }
  double minDist=1e16;
  VType center=-1;
  EType uFirstEdge=-1, vFirstEdge=-1;
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
        uFirstEdge=(u==center)?(-1):hl[u][i].previous_edge();
        vFirstEdge=(v==center)?(-1):hl[v][j].previous_edge();
      }
    }
  }
  if(center==-1)
    return minDist;
  edges.clear();

  if(uFirstEdge!=-1){
    edges.push_back(uFirstEdge);
    u=_ww.get_the_other_endpoint(u,uFirstEdge);
  }
  if(vFirstEdge!=-1){
    edges.push_back(vFirstEdge);
    v=_ww.get_the_other_endpoint(v,vFirstEdge);
  }
  while(u!=center){
    HLType hlItem=*std::lower_bound(hl[u].begin(),hl[u].end(),HLType(center,0,0));
    assert(hlItem.label()==center);
    edges.push_back(hlItem.previous_edge());
    u=_ww.get_the_other_endpoint(u,hlItem.previous_edge());
  }
  while(v!=center){
    HLType hlItem=*std::lower_bound(hl[v].begin(),hl[v].end(),HLType(center,0,0));
    assert(hlItem.label()==center);
    edges.push_back(hlItem.previous_edge());
    v=_ww.get_the_other_endpoint(v,hlItem.previous_edge());
  }
  return minDist;
}

CsrHLLoader::CsrHLLoader(const WeightedGraph &ww,const char *hlFilePath):_ww(ww){
  FILE* hlFile=OpenFile::open_r(hlFilePath);
  fscanf(hlFile,"%d",&n);
  hl=new std::vector<HLType> [n];
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

