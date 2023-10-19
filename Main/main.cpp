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
#include "OpenFile.h"
#include "KeyKG.h"

int test_HLLoader(int n,int m,uint32_t seed){
  std::string uwgPathString=(std::string(PROJECT_PATH)+std::string("/Resource/testHLLoader/edges.txt"));
  std::string wgPathString=(std::string(PROJECT_PATH)+std::string("/Resource/testHLLoader/wg.txt"));
  std::string hlPathString=(std::string(PROJECT_PATH)+std::string("/Resource/testHLLoader/hl.txt"));
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

int main(int argc, char **argv){
  // ./KeyKG [-args] FOLDER_NAME_IN_RESOURCE
  if(argc==1){
    std::cerr<<"Error: Too few args."<<std::endl;
    return -1;
  }
  if(argc==2){
    std::string dir=std::string(PROJECT_PATH)+std::string("/Resource/")+std::string(argv[1]);
    std::string uwgPath=dir+std::string("/edges.txt");
    std::string wgPath=dir+std::string("/wg.txt");
    std::string hlPath=dir+std::string("/hl.txt");
    std::string kmPath=dir+std::string("/keymap.txt");
    std::string qPath=dir+std::string("/queries.txt");
    if(!OpenFile::file_exist(wgPath.c_str())){// no weighted graph file
      WeightedGraph::gen_weighted_graph_file(uwgPath.c_str(),wgPath.c_str(),2336);
    }
    WeightedGraph ww(wgPath.c_str());
    if(!OpenFile::file_exist(hlPath.c_str())){
      SHL shl(200);
      shl.gen_hub_label_file(hlPath.c_str(),wgPath.c_str());
    }
    CsrHLLoader hl(ww,hlPath.c_str());

    std::vector<std::vector<VType>> groups;
    FILE* kmFile=OpenFile::open_r(kmPath.c_str());
    size_t groupTail;
    VType v;
    while(fscanf(kmFile,"%zu%d",&groupTail,&v)!=EOF){
      if(groupTail>=groups.size()){
        groups.emplace_back();
      }
      groups.back().push_back(v);
    }
    fclose(kmFile);

    FILE* qFile=OpenFile::open_r(qPath.c_str());
    size_t qIndex,prevIndex=0,groupIndex;
    KeyKG keyKG(ww,hl);
    while(fscanf(qFile,"%zu%zu",&qIndex,&groupIndex)!=EOF){
      if(qIndex!=prevIndex){
        keyKG.run((dir+"/"+std::to_string(prevIndex)+".txt").c_str());
        keyKG.reset_group_number();
        prevIndex=qIndex;
      }
      keyKG.add_group(groups[groupIndex].size(),groups[groupIndex].data());
    }
    keyKG.run((dir+"/"+std::to_string(prevIndex)+".txt").c_str());
    fclose(qFile);
  }
  return 0;
}