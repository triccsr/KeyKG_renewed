//
// Created by triccsr on 9/16/23.
//

#include <cstdio>
#include <algorithm>
#include "WeightedGraph.h"
#include "RandomDouble.h"

WeightedGraph::WeightedGraph(FILE *weightedGraphFile) {
    outEdges=nullptr;
    load_weighted_graph_file(weightedGraphFile);
}
WeightedGraph::~WeightedGraph() {
    delete[] outEdges;
}

void WeightedGraph::add_edge(VType src, VType dst, double weight,EType edgeIndex) {
    outEdges[src].emplace_back(dst,weight,edgeIndex);
}
void WeightedGraph::load_weighted_graph_file(FILE * weightedGraphFile) {
    delete[] outEdges;
    EType m;
    fscanf(weightedGraphFile,"%d%d",&n,&m);
    outEdges = new std::vector<WeightedOutEdge>[n];
    for(VType i=0;i<m;++i){
        VType u,v;
        double w;
        fscanf(weightedGraphFile,"%d%d%lf",&u,&v,&w);
        outEdges[u].emplace_back(v,w,i);
        outEdges[v].emplace_back(u,w,i);
    }
    for(VType i=0;i<n;++i){
        outEdges[i].shrink_to_fit();
    }
}

VType WeightedGraph::vertex_count() const {
    return n;
}

const std::vector<WeightedOutEdge> & WeightedGraph::outEdgesOf(VType ver) const {
    return outEdges[ver];
}

void WeightedGraph::gen_weighted_graph_file(FILE *unweightedGraphFile, FILE* dstFile,uint32_t seedU) {
    std::vector<std::pair<VType,VType> > uwEdges;
    VType u,v;
    VType fileN=0;
    EType fileM=0;
    while(fscanf(unweightedGraphFile,"%d%d", &u, &v) != EOF){
        uwEdges.emplace_back(u,v);
        fileN=std::max(fileN,std::max(u,v));
        fileM+=1;
    }
    fprintf(dstFile,"%d %d\n",fileN+1,fileM);
    RandomDouble rd(0.1,1000.0,seedU);
    for(auto uwEdge:uwEdges){
        fprintf(dstFile,"%d %d %.6f\n",uwEdge.first,uwEdge.second,rd.rand_double());
    }
}

VType WeightedGraph::outDegreeOf(VType ver) const {
    return (VType)outEdges[ver].size();
}
