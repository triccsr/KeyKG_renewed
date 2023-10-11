//
// Created by triccsr on 9/25/23.
//

#include "HubLabel.h"
#include "BC.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <set>
#include <queue>
void HubLabel::gen_hub_label_file(const WeightedGraph &ww, int pivotNum, const char *dstFilePath) {
  std::cerr << "Start calculating hub labels" << std::endl;
  std::vector<std::pair<double, VType>> ss;
  BC bc(ww, pivotNum);
  ss.resize(static_cast<unsigned long>(ww.vertex_count()));
  for (VType v = 0; v < ww.vertex_count(); ++v) {
    auto index = static_cast<unsigned long>(v);
    ss[index].first = bc.get_BC_of(v);
    ss[index].second = v;
  }
  std::sort(ss.begin(), ss.end(), std::greater<std::pair<double, VType>>());

  std::vector<bool> visited(static_cast<size_t>(ww.vertex_count()), false);
  std::vector<EType> pred(static_cast<size_t>(ww.vertex_count(), -1));
  std::vector<double> d(static_cast<size_t>(ww.vertex_count()), doubleINF);
  auto *L = new std::set<HLType>[ww.vertex_count()];

  VType vIndex = 0;
  for (auto &s : ss) {
    VType v = s.second;
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
  std::cerr << "Finish calculating hub labels, start writing hub label file" << std::endl;
  FILE *dstFile = fopen(dstFilePath, "w");
  try {
    if (dstFile == nullptr) {
      throw std::invalid_argument("Cannot create file: " + std::string(dstFilePath));
    }
  }
  catch (const std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
  }
  fprintf(dstFile, "%d\n", ww.vertex_count()); //First line an integer n, means that there are n vertices in the graph.
  for (VType i = 0; i < ww.vertex_count(); ++i) {
    fprintf(dstFile, "%zu  ", L[i].size());
    for (auto element : L[i]) {
      fprintf(dstFile, "%d %d %.8f  ", element.label(), element.previous_edge(), element.dist());
    }
    fprintf(dstFile, "\n");
  }

  std::cerr << "Finish writing hub label file" << std::endl;
}

HubLabel::HubLabel(const char *filePath) {
  std::cerr << "Start reading hub label file" << std::endl;
  FILE *file = fopen(filePath, "r");
  fscanf(file, "%d", &wgVerticesCount);
  //init attribute variables
  hubLabelOf = new std::vector<HLType>[wgVerticesCount];
  hubLabelSize = 0;

  for (VType v = 0; v < wgVerticesCount; ++v) {
    size_t vSize;
    fscanf(file, "%zu", &vSize);
    hubLabelSize += vSize;
    hubLabelOf[v].reserve(vSize);
    for (size_t i = 0; i < vSize; ++i) {
      VType label, prev;
      double dist;
      fscanf(file, "%d%d%lf", &label, &prev, &dist);
      hubLabelOf[v].emplace_back(label, prev, dist);
    }
  }
  fclose(file);
  std::cerr << "Finish reading hub label file" << std::endl;
}
HubLabel::~HubLabel() {
  delete[] hubLabelOf;
}
size_t HubLabel::hub_label_size() const {
  return hubLabelSize;
}
double HubLabel::get_dist(VType u, VType v, std::set<HLType> &uHL, const std::set<HLType> &vHL) {
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
double HubLabel::get_dist(VType u, VType v) {

}
std::vector<VType> HubLabel::get_shortest_path(VType u, VType v) {
  return std::vector<VType>();
}

