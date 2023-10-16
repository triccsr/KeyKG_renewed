#include <iostream>
#include <cmath>
#include <algorithm>
#include "WeightedGraph.h"
#include "CsrHLLoader.h"
#include "SHL.h"
#include "TestHLLoader.h"
#include "RandomGraph.h"
#include "config.h"
#include "PLL.h"

int main(int argc, char **argv){
  int n,m;
  uint32_t seed;
  scanf("%d%d%u",&n,&m,&seed);
  std::string uwgPathString=(std::string(PROJECT_PATH)+std::string("/Resource/test/uwg.txt"));
  std::string wgPathString=(std::string(PROJECT_PATH)+std::string("/Resource/test/wg.txt"));
  std::string hlPathString=(std::string(PROJECT_PATH)+std::string("/Resource/test/hl.txt"));
  RandomGraph::gen_random_graph(n,m,uwgPathString.c_str(),seed);
  WeightedGraph::gen_weighted_graph_file(uwgPathString.c_str(),wgPathString.c_str());
  WeightedGraph ww(wgPathString.c_str());
  SHL shl(20);
  shl.gen_hub_label_file(hlPathString.c_str(),wgPathString.c_str());
  CsrHLLoader myHL(ww,hlPathString.c_str());
  TestHLLoader test(ww);
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      std::vector<EType> myEdges,juryEdges;
      double myDist=myHL.get_sp(i,j,myEdges);
      double juryDist=test.get_sp(i,j,juryEdges);
      std::sort(myEdges.begin(),myEdges.end());
      std::sort(juryEdges.begin(),juryEdges.end());
      if(fabs(myDist-juryDist)>1e-6){
        fprintf(stderr,"Error: pair %d %d, your = %.6f, jury's = %.6f\n",i,j,myDist,juryDist);
        return -1;
      }
      if(myEdges!=juryEdges){
        double mySum=0.0,jurySum=0.0;
        for(EType e:myEdges){
          mySum+=ww.get_edge_info(e).weight();
        }

        for(EType e:juryEdges){
          jurySum+=ww.get_edge_info(e).weight();
        }
        if(fabs(mySum-jurySum)>1e-6){
          fprintf(stderr,"Error: pair %d %d, your edges = ",i,j);
          for(EType e:myEdges){
            fprintf(stderr,"%d ",e);
          }
          fprintf(stderr,", jury's edges = ");
          for(EType e:juryEdges){
            fprintf(stderr,"%d ",e);
          }
          fprintf(stderr,"your weight sum = %.6f, jury's = %.6f\n",mySum,jurySum);
          return -1;
        }
      }

    }
    fprintf(stderr,"Pass: vertex %d\n",i);
  }
  return 0;
}