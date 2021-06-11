#include "fsm.h"

namespace stuff {
  namespace aob {
    state_t fsm::next(state_t state, byte b) const {
      while (moveTo[state][b] == -1) {
        state = failureLink[state];
      }
      return moveTo[state][b];
    }

    void fsm::build(const vector<string_view>& patterns) {
      // Initialize first state (empty array)
      moveTo.push_back({});
      moveTo[0].fill(-1);

      for (const auto& pattern : patterns) {
        insert(pattern);
      }

      // Make root node point to itself for all bytes that are not at the start of any pattern
      for (int i = 0; i < alphabetSize; i++) {
        if (moveTo[0][i] == -1) {
          moveTo[0][i] = 0;
        }
      }

      createLinks();
    }

    void fsm::insert(const string_view& pattern) {}

    void fsm::createLinks() {
      failureLink.insert(failureLink.begin(), moveTo.size(), -1);
    }

  }  // namespace aob
}  // namespace stuff
