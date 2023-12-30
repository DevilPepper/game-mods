#pragma once

#include <Windows.h>
#include <gamepad.h>
#include <types/address.h>

#include <string_view>

#include "../model/Addresses.h"

namespace plugin {
  using gamepad::Gamepad;
  using model::Addresses;
  using stuff::types::Pointer;

  constexpr std::string_view settings = "TheFlash.yaml";

  class Hermes {
   private:
    Addresses addresses;
    intptr_t walkSpeedOffset = 0x934;
    intptr_t runSpeedOffset = 0x954;
    intptr_t dashSpeedOffset = 0x964;
    intptr_t sprintSpeedOffset = 0x9ac;
    // intptr_t gravitySpeedOffset = 0xbc;

    int expBase;
    int direction = 1;
    float walk = 1.12;
    float run = 1;
    float dash = 1.20;
    float sprint = 1.35;
    // float gravity = 1.32;

   public:
    Hermes();
    void handleInput(const Gamepad& input);
  };
}  // namespace plugin
