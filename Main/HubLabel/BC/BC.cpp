//
// Created by triccsr on 9/24/23.
//

#include <algorithm>
#include <queue>
#include <stdexcept>
#include <iostream>
#include "BC.h"

void BC::add_delta_from(int src) {
	typedef std::pair<double, VType> DisPair;
	//memset(ok,0, sizeof (bool) * static_cast<unsigned long>(ww.vertex_count()));
	for (VType v = 0; v < ww.vertex_count(); ++v) {
		ok[v] = false;
		spCount[v] = 0;
		dis[v] = doubleINF;
		delta[v] = 0.0;
		pred[v].clear();
	}
	std::priority_queue<DisPair, std::vector<DisPair>, std::greater<DisPair>> pq;
	auto disSort = new VType[ww.vertex_count()];
	VType disSortTail = 0;
	pq.emplace(0.0, src);
	dis[src] = 0.0;
	spCount[src] = 1;
	for (VType loop = 0; loop < ww.vertex_count(); ++loop) {
		while (!pq.empty() && ok[pq.top().second]) {
			pq.pop();
		}
		if (pq.empty())
			break;
		VType v = pq.top().second;
		pq.pop();
		ok[v] = true;
		disSort[disSortTail++] = v;
		try {
			if (spCount[v] < 0) {
				throw std::overflow_error("delta");
			}
		}
		catch (std::overflow_error const &ex) {
			std::cerr << "delta overflow: vertex index" << v << std::endl;
		}
		for (WeightedOutEdge woe : ww.out_edges_of(v)) {
			double newDis = dis[v] + woe.weight();
			if (newDis < dis[woe.to()]) {
				dis[woe.to()] = newDis;
				pq.emplace(dis[woe.to()], woe.to());
			}

			if (newDis - dis[woe.to()] < -eps) { // shortest path from src to woe.to() passes v
				spCount[woe.to()] = spCount[v];
				pred[woe.to()].clear();
				pred[woe.to()].push_back(v);
			} else if (newDis - dis[woe.to()] < eps) { // approximately equal
				spCount[woe.to()] += spCount[v];
				pred[woe.to()].push_back(v);
			}
		}
	}
	for (VType dIdx = disSortTail - 1; dIdx >= 0; --dIdx) {
		VType w = disSort[dIdx];
		for (VType v : pred[w]) {
			delta[v] += ((double)spCount[v] / (double)spCount[w]) * (1.0 + delta[w]);
		}
		if (w != src) {
			bc[w] += delta[w];
		}
	}
	delete[] disSort;
}

BC::BC(const WeightedGraph &argWW, int pivotNum) : ww(argWW) {
	spCount = new uint64_t[ww.vertex_count()];
	delta = new double[ww.vertex_count()];
	dis = new double[ww.vertex_count()];
	ok = new bool[ww.vertex_count()];
	pred = new std::vector<VType>[ww.vertex_count()];

	bc = new double[ww.vertex_count()];

	auto degreePairs = new std::pair<VType, VType>[ww.vertex_count()];
	for (VType v = 0; v < ww.vertex_count(); ++v) {
		bc[v] = 0.0;
		degreePairs[v] = std::make_pair(ww.out_degree_of(v), v);
	}
	std::sort(degreePairs, degreePairs + ww.vertex_count(), std::greater<std::pair<VType, VType>>());
	for (int i = 0; i < pivotNum; ++i) {
		add_delta_from(degreePairs[i].second);
	}

	delete[] spCount;
	delete[] delta;
	delete[] ok;
	delete[] dis;
	delete[] pred;
}

double BC::get_BC_of(VType ver) {
	return bc[ver];
}

BC::~BC() {

	delete[] bc;
}
