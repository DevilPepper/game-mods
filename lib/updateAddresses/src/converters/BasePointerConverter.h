#pragma once

#include <types/address.h>
#include <yaml-cpp/yaml.h>

#include "../model/BasePointer.h"

namespace YAML {
  using model::BasePointer;
  using stuff::types::Pointer;

  template <>
  struct convert<BasePointer> {
    static bool decode(const Node& node, BasePointer& rhs) {
      rhs.address = node["address"].as<Pointer>();
      rhs.source = node["source"].as<Pointer>();
      return true;
    }
  };
}  // namespace YAML
