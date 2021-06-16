#pragma once

#include <types/address.h>
#include <yaml-cpp/yaml.h>

#include <map>
#include <string>

#include "../model/Addresses.h"
#include "../model/BasePointer.h"

namespace YAML {
  using model::Addresses;
  using std::string;

  template <>
  struct convert<Addresses> {
    static bool decode(const Node& node, Addresses& rhs) {
      rhs.basePointers = node["basePointers"].as<map<string, model::BasePointer>>();
      rhs.functions = node["functions"].as<map<string, stuff::types::Pointer>>();
      return true;
    }
  };
}  // namespace YAML
