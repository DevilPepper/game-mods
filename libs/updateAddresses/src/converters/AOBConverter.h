#pragma once

#include <yaml-cpp/yaml.h>

#include <string>

#include "../model/AOB.h"

namespace YAML {
  using model::AOB;
  using std::string;

  template <>
  struct convert<AOB> {
    static bool decode(const Node& node, AOB& rhs) {
      rhs.aob = node["aob"].as<string>();
      rhs.offset = node["offset"].as<int>(0);
      return true;
    }
  };
}  // namespace YAML
