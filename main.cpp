#include <iostream>
#include "WeightedGraph.h"

int main() {
    FILE* uwFile=fopen("../resource/testuwgraph.txt","r");
    FILE* dstFile=fopen("../resource/testwg.txt","w");
    WeightedGraph::gen_weighted_graph_file(uwFile,dstFile,2333);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
