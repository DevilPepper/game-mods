#pragma once

#include <types/address.h>
#include <yaml-cpp/yaml.h>

#include <vector>

#include "Addresses.h"

namespace YAML {
  using model::Addresses;
  using stuff::types::Pointer;

  template <>
  struct convert<Addresses> {
    static bool decode(const Node& node, Addresses& rhs) {
      rhs.zone = node["zone"].as<Pointer>();

      rhs.session_quest = node["session_quest"].as<Pointer>();
      return true;
    }
  };
}  // namespace YAML
