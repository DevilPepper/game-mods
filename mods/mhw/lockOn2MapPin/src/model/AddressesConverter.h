#pragma once

#include <types/address.h>
#include <yaml-cpp/yaml.h>

#include <vector>

#include "Addresses.h"

using stuff::types::Pointer;

namespace YAML {
  template <>
  struct convert<Addresses> {
    static bool decode(const Node& node, Addresses& rhs) {
      rhs.zone = node["zone"].as<Pointer>();

      rhs.quest_manager = node["quest_manager"].as<Pointer>();
      rhs.pin_params = node["pin_params"].as<Pointer>();
      rhs.display_options = node["display_options"].as<Pointer>();
      rhs.monsters = node["monsters"].as<Pointer>();

      rhs.fnPinMap = (InvokableConsumer)node["fnPinMap"].as<Pointer>();
      rhs.fnLockOnIncrement = node["fnLockOnIncrement"].as<Pointer>();
      return true;
    }
  };
}  // namespace YAML
