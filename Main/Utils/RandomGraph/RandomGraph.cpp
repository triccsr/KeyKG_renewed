//
// Created by tricc on 2023/10/15.
//

#include <set>
#include "RandomGraph.h"
#include "OpenFile.h"
#include "RandomMT.h"
void RandomGraph::gen_random_graph(int n, int m, const char *dstPath) {
  FILE* dstFile=OpenFile::open_w(dstPath);
  RandomMT<int> rd(0,n-1,233);
  std::set<std::pair<int,int>> edgeSet;
  for(int i=0;i<m;++i){
    int u=rd.rand_mt();
    int v=rd.rand_mt();
    if(u>v)std::swap(u,v);
    if(u==v||edgeSet.count(std::make_pair(u,v))){
      --i;
    }
    else{
      fprintf(dstFile,"%d %d\n",u,v);
      edgeSet.emplace(u,v);
    }
  }

  fclose(dstFile);
}
