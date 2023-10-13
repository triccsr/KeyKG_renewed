//
// Created by tricc on 2023/10/12.
//

#include <set>
#include <queue>
#include <iostream>
#include "DijkstraBasedAbstract.h"
#include "OpenFile.h"

double DijkstraBasedAbstract::get_dist(VType u, VType v, const std::set<HLType> &uHL, const std::set<HLType> &vHL) const {
  double res = doubleINF;
  for (auto uIt = uHL.begin(), vIt = vHL.begin(); uIt != uHL.end() && vIt != vHL.end(); ++uIt) {
    while (vIt != vHL.end() && vIt->label() < uIt->label()) {
      ++vIt;
    }
    if (vIt == vHL.end())break;
    if (uIt->label() == vIt->label()) {
      res = std::min(res, uIt->dist() + vIt->dist());
    }
  }
  return res;
}

void DijkstraBasedAbstract::dijkstra_in_order(const std::vector<VType> &orderedVertices) {
  std::vector<bool> visited(static_cast<size_t>(ww.vertex_count()), false);
  std::vector<EType> pred(static_cast<size_t>(ww.vertex_count(), -1));
  std::vector<double> d(static_cast<size_t>(ww.vertex_count()), doubleINF);

  VType vIndex = 0;
  for (auto &v : orderedVertices) {
    std::fprintf(stderr, "%d: vertex %d dijkstra starts\n", vIndex, v);
    std::vector<VType> allVisited; //used for reverting arrays visited and d
    std::vector<VType> needUpdateLabel;//vertices whose Label needs updating
    d[v] = 0.0;
    std::priority_queue<std::pair<double, VType>,
                        std::vector<std::pair<double, VType>>,
                        std::greater<std::pair<double, VType>>> pq;
    pq.emplace(d[v], v);
    while (!pq.empty()) {
      while (!pq.empty() && visited[pq.top().second]) {
        pq.pop();
      }
      if (pq.empty())break;
      VType u = pq.top().second;
      pq.pop();
      visited[u] = true;
      allVisited.push_back(u);
      if (d[u] < get_dist(u, v, L[u], L[v])) {
        needUpdateLabel.push_back(u);
        for (WeightedOutEdge outEdge : ww.out_edges_of(u)) {
          if (d[u] + outEdge.weight() < d[outEdge.to()]) {
            d[outEdge.to()] = d[u] + outEdge.weight();
            pred[outEdge.to()] = outEdge.edge_index();
            pq.emplace(d[outEdge.to()], outEdge.to());
          }
        }
      }
    }
    for (VType u : needUpdateLabel) {
      L[u].emplace(v, pred[u], d[u]);
    }
    for (VType u : allVisited) {
      visited[u] = false;
      pred[u] = -1;
      d[u] = doubleINF;
    }
    std::fprintf(stderr,
                 "%d: vertex %d dijkstra finished, updates HL of %zu vertices\n",
                 vIndex,
                 v,
                 needUpdateLabel.size());
    ++vIndex;
  }
  std::cerr << "Finish calculating hub labels." << std::endl;
}

void DijkstraBasedAbstract::write_hub_label2file(const char *dstFilePath) {
  FILE* dstFile=OpenFile::open_w(dstFilePath);
  std::cerr<<"Start writing hub label to file..."<<std::endl;
  fprintf(dstFile, "%d\n", ww.vertex_count()); //First line an integer n, means that there are n vertices in the graph.
  for (VType i = 0; i < ww.vertex_count(); ++i) {
    fprintf(dstFile, "%zu  ", L[i].size());
    for (auto element : L[i]) {
      fprintf(dstFile, "%d %d %.8f  ", element.label(), element.previous_edge(), element.dist());
    }
    fprintf(dstFile, "\n");
    std::cerr << "Finish writing hub label file, close file and delete L" << std::endl;
  delete L;
  fclose(dstFile);
}

void DijkstraBasedAbstract::gen_hub_label_file(const char *dstPath, const char *wgFilePath) {
  ww=WeightedGraph(wgFilePath);
  std::vector<VType> orderedVertices=get_ordered_vertices();
  dijkstra_in_order(orderedVertices);
  write_hub_label2file(dstPath);
}