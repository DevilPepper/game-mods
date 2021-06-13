#pragma once

#include <fstream>
#include <functional>
#include <string_view>
#include <vector>

#include "fsm.h"
#include "types/address.h"
#include "types/ghidra.h"

namespace stuff {
  namespace aob {
    namespace PatternSearch {
      using ghidra::types::byte;
      using stuff::types::Pointer;

      void findInMemory(const fsm& automaton,
                        const byte* begin,
                        const byte* end,
                        std::function<void(unsigned int, Pointer)> handleFoundAddress);

      void findInMemory(const std::vector<std::string_view>& patterns,
                        const byte* begin,
                        const byte* end,
                        std::function<void(unsigned int, Pointer)> handleFoundAddress,
                        char trailingBytes = '-');
    }  // namespace PatternSearch
  }    // namespace aob
}  // namespace stuff
