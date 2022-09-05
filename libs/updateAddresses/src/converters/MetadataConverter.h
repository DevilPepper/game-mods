#pragma once

#include <yaml-cpp/yaml.h>

#include <unordered_map>
#include <string>

#include "../model/AOB.h"
#include "../model/Metadata.h"
#include "AOBConverter.h"

namespace YAML {
  using model::AOB;
  using model::Metadata;
  using std::unordered_map;
  using std::string;

  template <>
  struct convert<Metadata> {
    static bool decode(const Node& node, Metadata& rhs) {
      rhs.basePointers = node["basePointers"].as<unordered_map<string, AOB>>();
      rhs.functions = node["functions"].as<unordered_map<string, AOB>>();
      return true;
    }
  };
}  // namespace YAML
