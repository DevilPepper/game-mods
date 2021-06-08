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
    intptr_t walkSpeedOffset = 0x940;
    intptr_t runSpeedOffset = 0x980;
    intptr_t dashSpeedOffset = 0x9b0;

    int expBase;
    float walk = 1.12;
    float run = 1;
    float dash = 1.20;

   public:
    Addresses addresses;
    Hermes();
    void handleInput(const Gamepad& input);
  };
}  // namespace plugin
