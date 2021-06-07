#include "memory.h"

#include <iostream>

namespace stuff {
  namespace memory {
    using namespace std;
    intptr_t followPointers(intptr_t base, const vector<intptr_t>& offsets, intptr_t exeBase) {
      auto addy = *(intptr_t*)(base + exeBase);
      int i = 0;
      for (; i < offsets.size() - 1; i++) {
        addy = *(intptr_t*)(addy + offsets[i]);
      }
      return addy + offsets[i];
    }
    intptr_t followPointer(intptr_t base, intptr_t offset, intptr_t exeBase) {
      auto addy = *(intptr_t*)(base + exeBase);
      return addy + offset;
    }
  }  // namespace memory
}  // namespace stuff
