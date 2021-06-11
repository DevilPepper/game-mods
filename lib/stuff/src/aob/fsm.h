#pragma once

#include <array>
#include <optional>
#include <string_view>
#include <vector>

#include "OutputNode.h"
#include "types/ghidra.h"

namespace stuff {
  namespace aob {
    using state_t = int;
    using ghidra::types::byte;
    using std::string_view;
    using std::vector;

    inline constexpr int alphabetSize = 257;

    /**
     * This is an implementation of the automaton described in
     *
     * Alfred V. Aho and Margaret J. Corasick. 1975.
     * Efficient string matching: an aid to bibliographic search.
     * <i>Commun. ACM</i> 18, 6 (June 1975), 333–340.
     * DOI:https://doi.org/10.1145/360825.360855
     *
     * Each node in the automaton is a byte with "byte" 256 used for wildcards
     */
    struct fsm {
      /**
       * Each state either has an <code>OutputNode</code> or not.
       * <code>OutputNode</code> is a simple linked list allowing "malformed" links.
       *
       * A linked list starting at <code>output[i]</code> contains:
       * - the AOB found at node <code>i</code>
       * - the AOB found if you traversed all available dictionary links from node <code>i</code>
       */
      vector<std::optional<OutputNode>> output;

      void build(const vector<string_view>& patterns);
      state_t next(state_t state, byte b) const;

     private:
      /**
       * I use an array for each state instead of a map
       * because map lookup is O(log(n))
       * unordered_map would be a good alternative, but it'll basically be the same
       */
      vector<std::array<state_t, alphabetSize>> moveTo;
      vector<state_t> failureLink;

      void insert(const string_view& pattern);

      // BFS trie to create failure links and dictionary links
      void createLinks();
    };
  }  // namespace aob
}  // namespace stuff
