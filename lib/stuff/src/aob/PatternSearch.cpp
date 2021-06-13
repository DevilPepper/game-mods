#include "PatternSearch.h"

namespace stuff {
  namespace aob {
    namespace PatternSearch {
      void findInMemory(const fsm& automaton,
                        byte* begin,
                        byte* end,
                        std::function<void(unsigned int, Pointer)> handleFoundAddress) {
        state_t state = 0;
        auto cursor = begin;
        do {
          state = automaton.next(state, *cursor);
          if (automaton.output[state].has_value()) {
            auto output = &(automaton.output[state].value());
            while (output != nullptr) {
              if (output->isMatch) {
                handleFoundAddress(output->patternIndex, (Pointer)(cursor - (output->patternSize)));
              }
              output = output->next;
            }
          }
        } while (++cursor <= end);
      }

      void findInMemory(const std::vector<std::string_view>& patterns,
                        const byte* begin,
                        const byte* end,
                        std::function<void(unsigned int, Pointer)> handleFoundAddress,
                        char trailingBytes) {
        fsm automaton;
        automaton.build(patterns, trailingBytes);
        findInMemory(automaton, begin, end, handleFoundAddress);
      }
    }  // namespace PatternSearch
  }    // namespace aob
}  // namespace stuff
