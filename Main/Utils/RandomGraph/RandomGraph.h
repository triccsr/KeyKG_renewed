//
// Created by tricc on 2023/10/15.
//

#ifndef KEYKG_MAIN_UTILS_RANDOMGRAPH_RANDOMGRAPH_H_
#define KEYKG_MAIN_UTILS_RANDOMGRAPH_RANDOMGRAPH_H_
#include <cstdint>

class RandomGraph {
 public:
  static void gen_random_graph(int n,int m,const char *dstPath,uint32_t seedU);
};

#endif //KEYKG_MAIN_UTILS_RANDOMGRAPH_RANDOMGRAPH_H_
