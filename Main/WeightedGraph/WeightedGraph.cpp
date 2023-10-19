//
// Created by triccsr on 9/16/23.
//

#include <cstdio>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "WeightedGraph.h"
#include "RandomMT.h"
#include "OpenFile.h"

WeightedGraph::WeightedGraph(const char *weightedGraphFilePath):outEdges(nullptr) {
  load_weighted_graph_file(weightedGraphFilePath);

}
WeightedGraph::~WeightedGraph() {
  delete[] outEdges;
}

void WeightedGraph::load_weighted_graph_file(const char *weightedGraphFilePath) {
  FILE *weightedGraphFile = OpenFile::open_r(weightedGraphFilePath);
  delete[] outEdges;
  EType m;
  fscanf(weightedGraphFile, "%d%d", &n, &m);
  outEdges = new std::vector<WeightedOutEdge>[n];
  edges.resize(static_cast<unsigned long long int>(m));
  for (EType i = 0; i < m; ++i) {
    VType u, v;
    double w;
    fscanf(weightedGraphFile, "%d%d%lf", &u, &v, &w);
    outEdges[u].emplace_back(v, w, i);
    outEdges[v].emplace_back(u, w, i);
    edges.at(i) = WeightedEdge(i, u, v, w);
  }
  for (VType i = 0; i < n; ++i) {
    outEdges[i].shrink_to_fit();
  }
  fclose(weightedGraphFile);
}

VType WeightedGraph::vertex_count() const {
  return n;
}

const std::vector<WeightedOutEdge> &WeightedGraph::out_edges_of(VType ver) const {
  return outEdges[ver];
}

void WeightedGraph::gen_weighted_graph_file(const char *unweightedGraphFilePath,
                                            const char *dstFilePath,
                                            uint32_t seedU) {
  FILE *unweightedGraphFile = fopen(unweightedGraphFilePath, "r");

  FILE *dstFile = fopen(dstFilePath, "w");
  try {
    if (unweightedGraphFile == nullptr) {
      throw std::invalid_argument("File not found: " + std::string(unweightedGraphFilePath));
    }
    if (dstFile == nullptr) {
      throw std::invalid_argument("Cannot create file: " + std::string(dstFilePath));
    }
  }
  catch (const std::invalid_argument &exc) {
    std::cerr << exc.what() << std::endl;
  }
  std::vector<std::pair<VType, VType> > uwEdges;
  VType u, v;
  VType fileN = 0;
  EType fileM = 0;
  while (fscanf(unweightedGraphFile, "%d%d", &u, &v) != EOF) {
    uwEdges.emplace_back(u, v);
    std::cerr<<"Weighted Graph reading edge: "<<u<<" "<<v<<std::endl;
    fileN = std::max(fileN, std::max(u, v));
    fileM += 1;
  }
  fprintf(dstFile, "%d %d\n", fileN + 1, fileM);
  RandomMT<double> rd(0.1, 1000.0, seedU);
  for (auto uwEdge : uwEdges) {
    fprintf(dstFile, "%d %d %.6f\n", uwEdge.first, uwEdge.second, rd.rand_mt());
  }
  fclose(unweightedGraphFile);
  fclose(dstFile);
}

VType WeightedGraph::out_degree_of(VType ver) const {
  return (VType)outEdges[ver].size();
}
WeightedEdge WeightedGraph::get_edge_info(EType edgeIndex) const{
  return edges[static_cast<unsigned long long int>(edgeIndex)];
}
VType WeightedGraph::get_the_other_endpoint(VType src, EType edgeIndex) const{
  VType u=edges[static_cast<unsigned long long int>(edgeIndex)].u();
  VType v=edges[static_cast<unsigned long long int>(edgeIndex)].v();
  if(u==src)
    return v;
  if(v==src)
    return u;
  try{
    throw std::invalid_argument("No endpoint in edge");
  }
  catch (const std::exception &e){
    std::cerr<<e.what()<<std::endl;
  }
}
WeightedGraph::WeightedGraph(WeightedGraph &&rValue):n(rValue.n),outEdges(rValue.outEdges),edges(std::move(rValue.edges)){
  rValue.outEdges= nullptr;
}
