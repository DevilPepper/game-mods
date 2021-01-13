#include "addy.h"

#include "json/json.h"

using namespace stuff::json;

namespace stuff {
  namespace addy {

    Addy::Addy() : offsets(map<string, vector<intptr_t>>()), address(map<string, intptr_t>()) {
      json = loadConfig(getAddressFilePath());
    }

    const intptr_t& Addy::getPointer(string node) {
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

    const Offsets& Addy::getOffsets(string node) {
      auto cached = offsets.find(node);
      if (cached != offsets.end()) {
        return cached->second;
      } else {
        auto computed = parseHexStrings(json[node]);
        offsets[node] = computed;
        return offsets[node];
      }
    }
  }  // namespace addy
}  // namespace stuff
