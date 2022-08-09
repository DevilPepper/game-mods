#pragma once

#include <types/address.h>
#include <yaml-cpp/yaml.h>

#include "../model/BasePointer.h"

namespace YAML {
  using model::BasePointer;
  using stuff::types::Pointer;

  template <>
  struct convert<BasePointer> {
    static Node encode(const BasePointer& rhs) {
      Node node;
      node["address"] = rhs.address;
      node["source"] = rhs.source;
      return node;
    }

    static bool decode(const Node& node, BasePointer& rhs) {
      rhs.address = node["address"].as<Pointer>();
      rhs.source = node["source"].as<Pointer>();
      return true;
    }
  };

  static Emitter& operator<<(Emitter& out, const BasePointer& rhs) {
    out << YAML::Hex;
    out << YAML::BeginMap;
    out << YAML::Key << "address";
    out << YAML::Value << rhs.address;
    out << YAML::Key << "source";
    out << YAML::Value << rhs.source;
    out << YAML::EndMap;
    return out;
  }
}  // namespace YAML
