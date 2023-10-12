//
// Created by tricc on 2023/10/12.
//

#include "DijkstraBasedAbstract.h"
#include "OpenFile.h"

void DijkstraBasedAbstract::dijkstra_in_order(const std::vector<VType> &orderedVertices) {

}

void DijkstraBasedAbstract::gen_hub_label_file(const char *dstPath, const char *wgFilePath) {
  FILE* hlFile=OpenFile::open_w(dstPath);
  FILE* wgFile=OpenFile::open_r(wgFilePath);
  write_hub_label(hlFile,wgFile);
  fclose(hlFile);
  fclose(wgFile);
}