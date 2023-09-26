//
// Created by triccsr on 9/24/23.
//

#include <algorithm>
#include <cstring>
#include "BC.h"


void BC::add_delta_from(int src) {
    memset(ok,0, sizeof (bool) * static_cast<unsigned long>(ww.vertex_count()));
    
}

BC::BC(const WeightedGraph &argWW, int pivotNum) : ww(argWW) {
    spCount = new uint64_t[ww.vertex_count()];
    delta = new double[ww.vertex_count()];
    bc = new double[ww.vertex_count()];
    ok = new bool[ww.vertex_count()];
    auto degreePairs=new std::pair<VType,VType>[ww.vertex_count()];
    for(VType v=0;v<ww.vertex_count();++v){
        bc[v]=0.0;
        degreePairs[v]=std::make_pair(ww.outDegreeOf(v),v);
    }
    std::sort(degreePairs,degreePairs+ww.vertex_count(),std::greater<std::pair<VType,VType>>());
    for(int i=0;i<pivotNum;++i){
        add_delta_from(degreePairs[i].second);
    }
}
double BC::get_BC_of(VType ver) {
    return bc[ver];
}

BC::~BC() {
    delete[] spCount;
    delete[] delta;
    delete[] bc;
    delete[] ok;
}

