#include <iostream>
#include "WeightedGraph.h"
#include "CsrHLLoader.h"
#include "SHL.h"
#include "TestHLLoader.h"
#include "RandomGraph.h"
#include "config.h"

int main(){
  int n,m;
  scanf("%d%d",&n,&m);
  std::string uwgPathString=(std::string(PROJECT_PATH)+std::string("/Resource/test/uwg.txt"));
  std::string wgPathString=(std::string(PROJECT_PATH)+std::string("/Resource/test/wg.txt"));
  std::string hlPathString=(std::string(PROJECT_PATH)+std::string("/Resource/test/hl.txt"));
  RandomGraph::gen_random_graph(n,m,uwgPathString.c_str());
  WeightedGraph::gen_weighted_graph_file(uwgPathString.c_str(),wgPathString.c_str());
  WeightedGraph ww(wgPathString.c_str());
  SHL shl(std::min(20,n/2));
  shl.gen_hub_label_file(hlPathString.c_str(),wgPathString.c_str());
  return 0;
}