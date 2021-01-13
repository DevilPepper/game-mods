#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace stuff {
  namespace json {
    nlohmann::json loadConfig(string fileName);
    vector<intptr_t> parseHexStrings(nlohmann::json node);
    intptr_t parseHexString(nlohmann::json node);
  }  // namespace json
}  // namespace stuff
