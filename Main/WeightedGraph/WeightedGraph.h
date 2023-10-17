//
// Created by triccsr on 9/16/23.
//

#ifndef KEYKG_WEIGHTEDGRAPH_H
#define KEYKG_WEIGHTEDGRAPH_H


#include <cstdint>
#include <vector>
#include <cstdio>
#include "WeightedOutEdge.h"
#include "../GraphTypes/GraphTypes.h"
#include "WeightedEdge.h"

class WeightedGraph {
    VType n{0};
    std::vector<WeightedOutEdge> *outEdges{nullptr};
    std::vector<WeightedEdge> edges;

public:
    WeightedGraph()=default;
    explicit WeightedGraph(const char* weightedGraphFilePath);
    explicit WeightedGraph(WeightedGraph&& rValue);
    ~WeightedGraph();
    void load_weighted_graph_file(const char *weightedGraphFilePath);
    VType vertex_count() const;
    VType out_degree_of(VType ver) const;
    const std::vector<WeightedOutEdge> & out_edges_of(VType ver) const;
    WeightedEdge get_edge_info(EType edgeIndex) const;
    VType get_the_other_endpoint(VType src,EType edgeIndex) const;
    static void gen_weighted_graph_file(const char* unweightedGraphFilePath,const char* dstFilePath,uint32_t seedU = 19260817); //gen weighted graph file from unweighted graph file
};


#endif //KEYKG_WEIGHTEDGRAPH_H
