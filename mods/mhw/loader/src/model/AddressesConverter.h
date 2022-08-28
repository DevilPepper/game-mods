#pragma once

#include <MHW/chat.h>
#include <Windows.h>
#include <types/address.h>
#include <yaml-cpp/yaml.h>

#include <vector>

#include "Addresses.h"

namespace YAML {
  using MHW::SendSystemMessage;
  using model::Addresses;
  using stuff::types::Pointer;

  template <>
  struct convert<Addresses> {
    static bool decode(const Node& node, Addresses& rhs) {
      auto functions = node["functions"];
      auto basePointers = node["basePointers"];
      auto exeBase = (Pointer)GetModuleHandle(NULL);

      rhs.zone = basePointers["zone"]["address"].as<Pointer>();

      rhs.chat_instance = exeBase + basePointers["chat_instance"]["address"].as<Pointer>();

      rhs.fnSendSystemMessage =
          (SendSystemMessage)(exeBase + functions["fnSendSystemMessage"].as<Pointer>());
      return true;
    }
  };
}  // namespace YAML
