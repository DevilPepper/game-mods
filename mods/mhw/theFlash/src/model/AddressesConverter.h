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
      auto basePointers = node["basePointers"];

      rhs.zone = basePointers["zone"]["address"].as<Pointer>();

      rhs.pl_params = basePointers["pl_params"]["address"].as<Pointer>();
      return true;
    }
  };
}  // namespace YAML
