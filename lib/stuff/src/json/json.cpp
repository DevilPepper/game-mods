#include "json.h"

#include <fstream>

namespace stuff {
  namespace json {
    nlohmann::json loadConfig(string fileName) {
      std::ifstream config(fileName);
      return nlohmann::json::parse(config);
    }

    vector<intptr_t> parseHexStrings(nlohmann::json node) {
      auto strings = node.get<vector<string>>();
      auto pointers = vector<intptr_t>();

      for (string str : strings) {
        pointers.push_back(std::stoll(str, nullptr, 16));
      }
      return pointers;
    }
    intptr_t parseHexString(nlohmann::json node) {
      auto str = node.get<string>();
      return std::stoll(str, nullptr, 16);
    }
  }  // namespace json
}  // namespace stuff
