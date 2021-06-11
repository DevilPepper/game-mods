#pragma once

#include <Windows.h>
#include <types/address.h>
#include <yaml-cpp/yaml.h>

#include <vector>

#include "Addresses.h"

namespace YAML {
  using model::Addresses;
  using model::InvokableConsumer;
  using stuff::types::Pointer;

  template <>
  struct convert<Addresses> {
    static bool decode(const Node& node, Addresses& rhs) {
      auto functions = node["functions"];
      auto basePointers = node["basePointers"];
      auto exeBase = (Pointer)GetModuleHandle(NULL);

      rhs.zone = basePointers["zone"]["address"].as<Pointer>();

      rhs.quest_manager = basePointers["quest_manager"]["address"].as<Pointer>();
      rhs.pin_params = basePointers["pin_params"]["address"].as<Pointer>();
      rhs.display_options = basePointers["display_options"]["address"].as<Pointer>();
      rhs.monsters = basePointers["monsters"]["address"].as<Pointer>();

      rhs.fnPinMap = (InvokableConsumer)(exeBase + functions["fnPinMap"].as<Pointer>());
      rhs.fnLockOnIncrement = exeBase + functions["fnLockOnIncrement"].as<Pointer>();
      return true;
    }
  };
}  // namespace YAML
