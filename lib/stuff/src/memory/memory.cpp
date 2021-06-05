#include "memory.h"

#include <iostream>

using namespace std;

namespace stuff {
  namespace memory {
    intptr_t followPointers(intptr_t base, const vector<intptr_t>& offsets, bool addExeBase) {
      auto addy = *(intptr_t*)(base + (addExeBase ? exeBase : 0));
      int i = 0;
      for (; i < offsets.size() - 1; i++) {
        addy = *(intptr_t*)(addy + offsets[i]);
      }
      return addy + offsets[i];
    }
    intptr_t followPointer(intptr_t base, intptr_t offset, bool addExeBase) {
      auto addy = *(intptr_t*)(base + (addExeBase ? exeBase : 0));
      return addy + offset;
    }
  }  // namespace memory
}  // namespace stuff
