#pragma once

#include <types/address.h>
#include <yaml-cpp/yaml.h>

#include <map>
#include <string>

#include "../model/Addresses.h"
#include "../model/BasePointer.h"
#include "BasePointerConverter.h"

namespace YAML {
  using model::Addresses;
  using std::map;
  using std::string;

  template <>
  struct convert<Addresses> {
    static Node encode(const Addresses& rhs) {
      Node node;
      node["basePointers"] = rhs.basePointers;
      node["functions"] = rhs.functions;
      return node;
    }

    static bool decode(const Node& node, Addresses& rhs) {
      rhs.basePointers = node["basePointers"].as<map<string, model::BasePointer>>();
      rhs.functions = node["functions"].as<map<string, stuff::types::Pointer>>();
      return true;
    }
  };

  static Emitter& operator<<(Emitter& out, const Addresses& rhs) {
    out << YAML::Hex;
    out << YAML::BeginMap;
    out << YAML::Key << "basePointers";
    out << YAML::Value << rhs.basePointers;
    out << YAML::Key << "functions";
    out << YAML::Value << rhs.functions;
    out << YAML::EndMap;
    return out;
  }
}  // namespace YAML
