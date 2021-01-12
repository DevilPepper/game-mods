#pragma once

#include <Windows.h>

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace stuff {
  namespace memory {
    extern intptr_t exeBase;

    intptr_t followPointers(intptr_t base, const vector<intptr_t>& offsets, bool addExeBase = true);
    intptr_t followPointer(intptr_t base, intptr_t offset, bool addExeBase = true);
    template <typename T>
    intptr_t readMem(intptr_t base,
                     const vector<intptr_t>& offsets,
                     T& buffer,
                     bool addExeBase = true) {
      auto addy = followPointers(base, offsets, addExeBase);
      buffer = *(T*)addy;
      return addy;
    }
    template <typename T>
    intptr_t writeMem(intptr_t base,
                      const vector<intptr_t>& offsets,
                      T& buffer,
                      bool addExeBase = true) {
      auto addy = followPointers(base, offsets, addExeBase);
      *(T*)addy = buffer;
      return addy;
    }
    template <typename T>
    intptr_t readMem(intptr_t base, intptr_t offset, T& buffer, bool addExeBase = true) {
      auto addy = followPointer(base, offset, addExeBase);
      buffer = *(T*)addy;
      return addy;
    }
    template <typename T>
    intptr_t writeMem(intptr_t base, intptr_t offset, T& buffer, bool addExeBase = true) {
      auto addy = followPointer(base, offset, addExeBase);
      *(T*)addy = buffer;
      return addy;
    }
  }  // namespace memory
}  // namespace stuff
