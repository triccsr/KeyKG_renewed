//
// Created by triccsr on 9/25/23.
//

#ifndef KEYKG_HUBLABEL_H
#define KEYKG_HUBLABEL_H


#include <cstdio>
#include "WeightedGraph.h"

class HubLabel {
  constexpr static double doubleINF=1e16;
public:
    static void gen_hub_label_file(const WeightedGraph &ww, int pivotNum);
    void load_hub_label_file(FILE* file);
};


#endif //KEYKG_HUBLABEL_H
