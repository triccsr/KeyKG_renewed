//
// Created by tricc on 2023/10/17.
//

#include <set>
#include <algorithm>
#include "KeyKG.h"
#include "Timer.h"
#include "OpenFile.h"
KeyKG::KeyKG(const WeightedGraph &ww,const CsrHLLoader &hlLoader):_g(0),_ww(ww), _hlLoader(hlLoader){
  for(auto & dhl : M){
    dhl.resize(static_cast<size_t>(_ww.vertex_count()));
    for(VType v=0;v<_ww.vertex_count();++v) {
      dhl[v] = DhlType();
    }
  }
}
void KeyKG::add_group(size_t groupSize, const VType *indexes) {
  try{
    if(_g==9){
      throw std::overflow_error("KeyKG error: Too many groups, cannot add.");
    }
  }
  catch (const std::overflow_error &e){
    std::cerr<<e.what()<<std::endl;
  }
  K[_g].resize(groupSize);
  for(size_t i=0; i<groupSize; ++i){
    K[_g][i]=indexes[i];
  }
  ++_g;
}
void KeyKG::run(const char *outFile) {
  FILE* out=OpenFile::open_w(outFile);
  int64_t startTime=Timer::micro_stamp();
  // construct dynamic HL for key sets K[1,_g)
  for(int i=1;i<_g;++i){
    for(VType v:K[i]){
      _hlLoader.insert_into_dhl(v,M[i]);
    }
  }

  //one star, from each key set, find the vertex nearest to center.
  VType verSetArr[2][_g];
  VType *uSet=verSetArr[0],*tmpSet=verSetArr[1];
  double minDistSum=1e16;
  for(VType one:K[0]){
    double distSum=0.0;
    tmpSet[0]=one;
    for(int i=1;i<_g;++i){
      std::pair<HLType,DhlType> tmp=_hlLoader.get_min_dhl(one,M[i]);
      distSum+=tmp.first.dist()+tmp.second.min_hl().dist();
      tmpSet[i]=tmp.second.min_vertex_index();// vertex nearest to one in K[i]
    }
    if(distSum<minDistSum){
      minDistSum=distSum;
      std::swap(uSet,tmpSet);
    }
  }

  //reset dynamic HL arrays
  for(int i=1;i<_g;++i){
    for(VType v:K[i]){
      _hlLoader.erase_from_dhl(v,M[i]);
    }
  }

  //min weight Tree
  std::set<VType> minTreeVertices;
  std::vector<EType> minTreeEdges;
  double minTreeWeight=1e16;

  for(int l=0;l<_g;++l){// enumerate the center
    std::set<VType> notInTreeSet;
    std::set<VType> treeVertices;
    std::vector<EType> treeEdges;
    for(int i=0;i<_g;++i){
      notInTreeSet.insert(uSet[i]);
    }
    VType center=uSet[l];
    treeVertices.insert(center);
    notInTreeSet.erase(center);
    _hlLoader.insert_into_dhl(center,M[0]);// M[0]: dHL for current tree

    while(!notInTreeSet.empty()){
      double minDist=1e16;
      VType src=-1,dst=-1;
      HLType srcHL,dstHL;

      //find the nearest t from current tree
      for(VType t:notInTreeSet){
        auto tmp=_hlLoader.get_min_dhl(t,M[0]); //get sp from t to current tree
        double tmpDist=tmp.first.dist()+tmp.second.min_hl().dist();
        if(tmpDist<minDist){
          minDist=tmpDist;
          src=t;
          srcHL=tmp.first;
          dst=tmp.second.min_vertex_index();
          dstHL=tmp.second.min_hl();
        }
      }

      std::vector<EType> newEdges;
      _hlLoader.get_sp_with_label(src,srcHL,dst,dstHL,newEdges);

      //add new edges into tree:
      // insert new vertices into treeVertices,
      // insert new edges to treeEdges,
      // update notInTreeSet and tree dHL
      for(EType eIdx:newEdges){
        WeightedEdge weightedEdge=_ww.get_edge_info(eIdx);
        if(!treeVertices.count(weightedEdge.u())){
          treeVertices.insert(weightedEdge.u());
          notInTreeSet.erase(weightedEdge.u());
          _hlLoader.insert_into_dhl(weightedEdge.u(),M[0]);
        }
        if(!treeVertices.count(weightedEdge.v())){
          treeVertices.insert(weightedEdge.v());
          notInTreeSet.erase(weightedEdge.v());
          _hlLoader.insert_into_dhl(weightedEdge.v(),M[0]);
        }
      }
      treeEdges.insert(treeEdges.end(),newEdges.begin(),newEdges.end());
    }

    //reset tree dHL
    for(VType v:treeVertices){
      _hlLoader.erase_from_dhl(v,M[0]);
    }

    //check new tree
    std::sort(treeEdges.begin(),treeEdges.end());
    treeEdges.erase(std::unique(treeEdges.begin(),treeEdges.end()),treeEdges.end());
    double treeWeight=0.0;
    for(EType eIdx:treeEdges){
      treeWeight+=_ww.get_edge_info(eIdx).weight();
    }
    if(treeWeight<minTreeWeight){
      minTreeVertices=std::move(treeVertices);
      minTreeEdges=std::move(treeEdges);
      minTreeWeight=treeWeight;
    }
  }
  int64_t endTime=Timer::micro_stamp();
  int64_t runTime=endTime-startTime;
  std::cerr<<"group number = "<<_g<<", run time = "<<runTime/1000<<"."<<runTime%1000<<"ms"<<std::endl;

  fprintf(out,"group number: %d\n",_g);

  fprintf(out,"run time: %lld.%lld ms\n",runTime/1000,runTime%1000);
  fprintf(out,"weight: %.6f\n",minTreeWeight);

  fprintf(out,"vertices: ");
  for(VType v:minTreeVertices){
    fprintf(out,"%d ",v);
  }
  fprintf(out,"\n");

  fprintf(out,"edges: ");
  for(EType e:minTreeEdges){
    fprintf(out,"<%d: %d %d %.6f> ",e,_ww.get_edge_info(e).u(),_ww.get_edge_info(e).v(),_ww.get_edge_info(e).weight());
  }
  fprintf(out,"\n");

  fprintf(out,"groups:\n");
  for(auto &group:K){
    for(VType v:group){
      fprintf(out,"%d ",v);
    }
    fprintf(out,"\n");
  }
  fclose(out);
}
int KeyKG::group_number() const {
  return _g;
}
void KeyKG::reset_group_number() {
  _g=0;
}

