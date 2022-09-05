#include "fsm.h"

#include <cctype>

#include <queue>

namespace stuff {
  namespace aob {
    // Straight up copied this:
    // https://www.geeksforgeeks.org/aho-corasick-algorithm-pattern-searching/

    constexpr auto WILDCARD_IDX = 256;

    state_t fsm::next(state_t state, byte b) const {
      while (moveTo[state][b] == -1 && moveTo[state][WILDCARD_IDX] == -1) {
        state = failureLink[state];
      }
      return moveTo[state][b] != -1 ? moveTo[state][b] : moveTo[state][WILDCARD_IDX];
    }

    void fsm::build(const vector<string_view>& patterns, char trailingBytes) {
      // Initialize first state (empty array)
      moveTo.push_back({});
      moveTo[0].fill(-1);
      output.emplace_back();

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
        }
        if (isxdigit(pattern[i])) {
          sscanf(&pattern[i], "%2hx", &b);
        } else {
          b = WILDCARD_IDX;
        }

        pathSize++;
        if (moveTo[state][b] == -1) {
          state_t newState = moveTo.size();

          moveTo.push_back({});
          moveTo[newState].fill(-1);
          output.emplace_back();

          moveTo[state][b] = newState;
        }
        state = moveTo[state][b];
      }

      // clang-format off
      output[state] = {
        .patternIndex = dbSize++,
        .patternSize = pathSize - 1,
        .isMatch = true
      };
      // clang-format on
    }

    void fsm::createLinks() {
      failureLink.resize(moveTo.size());
      state_t state, nextState, failure;

      std::queue<state_t> q;

      for (int b = 0; b < alphabetSize; b++) {
        state = moveTo[0][b];
        if (state != 0) {
          failureLink[state] = 0;
          q.push(state);
        }
      }

      while (!q.empty()) {
        state = q.front();
        q.pop();

        for (int b = 0; b < alphabetSize; b++) {
          nextState = moveTo[state][b];
          if (nextState != -1) {
            failure = failureLink[state];

            while (moveTo[failure][b] == -1) {
              failure = failureLink[failure];
            }

            failure = moveTo[failure][b];
            failureLink[nextState] = failure;

            if (output[failure].has_value()) {
              auto dictionaryLink = &(output[failure].value());
              if (output[nextState].has_value()) {
                output[nextState]->next = dictionaryLink;
              } else {
                // clang-format off
                output[nextState] = {
                  .next = dictionaryLink
                };
                // clang-format on
              }
            }
            q.push(nextState);
          }
        }
      }
    }
  }  // namespace aob
}  // namespace stuff
