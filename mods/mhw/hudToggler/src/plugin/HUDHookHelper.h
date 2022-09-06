#pragma once

#include <Windows.h>
#include <types/address.h>

#include <array>

#include "../model/Addresses.h"

namespace plugin {
  using model::Addresses;
  using stuff::types::Offsets;

  class HUDHookHelper {
   private:
    Addresses addresses;
    Offsets hud_settings{ 0xa8, 0x151F8C };
    std::array<bool, 8> toggles;

   public:
    bool wasActive;

    HUDHookHelper();
    void writeHUD();
  };
}  // namespace plugin
