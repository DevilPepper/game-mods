#include "fsm.h"

#include <ctype.h>

namespace stuff {
  namespace aob {
    state_t fsm::next(state_t state, byte b) const {
      while (moveTo[state][b] == -1) {
        state = failureLink[state];
      }
      return moveTo[state][b];
    }

    void fsm::build(const vector<string_view>& patterns, char trailingBytes) {
      // Initialize first state (empty array)
      moveTo.push_back({});
      moveTo[0].fill(-1);
      output.push_back({});

      for (const auto& pattern : patterns) {
        insert(pattern, trailingBytes);
      }

      // Make root node point to itself for all bytes that are not at the start of any pattern
      for (int i = 0; i < alphabetSize; i++) {
        if (moveTo[0][i] == -1) {
          moveTo[0][i] = 0;
        }
      }

      createLinks();
    }

    void fsm::insert(const string_view& pattern, char trailingBytes) {
      short b;
      state_t state = 0;
      int pathSize = 0;

      for (int i = 0; i < pattern.size(); i += 2) {
        while (isspace(pattern[i])) {
          i++;
        }
        if (pattern[i] == trailingBytes) {
          break;
        } else if (isxdigit(pattern[i])) {
          sscanf(&pattern[i], "%2hx", &b);
        } else {
          b = 256;
        }

        pathSize++;
        if (moveTo[state][b] == -1) {
          state_t newState = moveTo.size();

          moveTo.push_back({});
          moveTo[newState].fill(-1);
          output.push_back({});

          moveTo[state][b] = newState;
        }
        state = moveTo[state][b];
      }

      // clang-format off
      output[state] = {
        .patternIndex = dbSize++,
        .patternSize = pathSize,
        .isMatch = true
      };
      // clang-format on
    }

    void fsm::createLinks() {
      failureLink.insert(failureLink.begin(), moveTo.size(), -1);
    }

  }  // namespace aob
}  // namespace stuff
