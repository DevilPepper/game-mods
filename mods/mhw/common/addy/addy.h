#pragma once

#include <windows.h>

#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "stuff.h"
#pragma comment(lib, "stuff.lib")

using stuff::json::parseHexString;
using stuff::json::parseHexStrings;

using namespace stuff::functions;
using std::map;
using std::string;
using std::vector;

namespace MHW {
  typedef vector<intptr_t> Offsets;

  class Addy {
   private:
    map<string, Offsets> offsets;
    map<string, intptr_t> address;
    nlohmann::json json;

   public:
    Addy();

    template <typename T>
    const T& get(string node) {
      return json[node].get<T>();
    }

    template <>
    const intptr_t& get<intptr_t>(string node) {
      // Not O(1)???
      auto cached = address.find(node);
      if (cached != address.end()) {
        return cached->second;
      } else {
        auto computed = parseHexString(json[node]);
        address[node] = computed;
        return address[node];
      }
    }

    template <>
    const Offsets& get<Offsets>(string node) {
      auto cached = offsets.find(node);
      if (cached != offsets.end()) {
        return cached->second;
      } else {
        auto computed = parseHexStrings(json[node]);
        offsets[node] = computed;
        return offsets[node];
      }
    }
  };

}  // namespace MHW
