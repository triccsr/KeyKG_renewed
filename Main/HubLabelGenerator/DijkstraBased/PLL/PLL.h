//
// Created by tricc on 2023/10/13.
//

#ifndef KEYKG_MAIN_HUBLABELGENERATOR_DIJKSTRABASED_PLL_PLL_H_
#define KEYKG_MAIN_HUBLABELGENERATOR_DIJKSTRABASED_PLL_PLL_H_

#include "DijkstraBasedAbstract.h"

class PLL : DijkstraBasedAbstract{
    std::vector<VType> get_ordered_vertices() override;
};

#endif //KEYKG_MAIN_HUBLABELGENERATOR_DIJKSTRABASED_PLL_PLL_H_
