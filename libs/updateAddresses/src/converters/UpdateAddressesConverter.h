#pragma once

#include <yaml-cpp/yaml.h>

#include <string>

#include "../model/UpdateAddresses.h"

namespace YAML {
  using model::UpdateAddresses;
  using std::string;

  template <>
  struct convert<UpdateAddresses> {
    static bool decode(const Node& node, UpdateAddresses& rhs) {
      rhs.addresses = node["addresses"].as<string>();
      rhs.metadata = node["metadata"].as<string>();
      rhs.trailingBytes = node["trailingBytes"].as<char>('-');
      return true;
    }
  };
}  // namespace YAML
