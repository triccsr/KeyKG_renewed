//
// Created by triccsr on 9/16/23.
//

#ifndef KEYKG_TIMER_H
#define KEYKG_TIMER_H


#include <cstdint>

class Timer {
 public:
  static int64_t milli_stamp();
  static int64_t micro_stamp();
};


#endif //KEYKG_TIMER_H
