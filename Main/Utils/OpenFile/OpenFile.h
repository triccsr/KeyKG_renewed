//
// Created by tricc on 2023/10/12.
//

#ifndef KEYKG_UTILS_TRYFILEPTR_TRYFILEPTR_H_
#define KEYKG_UTILS_TRYFILEPTR_TRYFILEPTR_H_

#include <cstdio>

class OpenFile {
 public:
  static FILE* open_r(const char *rFilePath);
  static FILE* open_w(const char *wFilePath);
};

#endif //KEYKG_UTILS_TRYFILEPTR_TRYFILEPTR_H_
