//
// Created by triccsr on 9/16/23.
//

#ifndef KEYKG_WEIGHTEDGRAPH_H
#define KEYKG_WEIGHTEDGRAPH_H


#include <cstdint>
#include <vector>
#include "WeightedOutEdge.h"
#include "Timer.h"
#include "WeightedGraphDef.h"

class WeightedGraph {
    VType n;
    std::vector<WeightedOutEdge> *outEdges;
    void add_edge(VType src,VType dst,double weight,EType edgeIndex);
    void load_weighted_graph_file(FILE* weightedGraphFile);
public:
    WeightedGraph()=default;
    explicit WeightedGraph(FILE* weightedGraphFile);
    ~WeightedGraph();
    VType vertex_count() const;
    VType outDegreeOf(VType ver) const;
    const std::vector<WeightedOutEdge> & outEdgesOf(VType ver) const;
    static void gen_weighted_graph_file(FILE* unweightedGraphFile,FILE* dstFile,uint32_t seedU = 19260817); //gen weighted graph file from unweighted graph file
};


#endif //KEYKG_WEIGHTEDGRAPH_H
