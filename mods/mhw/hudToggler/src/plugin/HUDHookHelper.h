#pragma once

#include <Windows.h>
#include <gamepad.h>
#include <types/address.h>

#include "../model/Addresses.h"

namespace plugin {
  using gamepad::Button;
  using gamepad::Gamepad;
  using model::Addresses;
  using stuff::types::Offsets;

  class HUDHookHelper {
   private:
    Addresses addresses;
    static const Button HUDToggle = Button::L1;
    static const Button SubtitlesToggle = Button::Select;

    intptr_t subtitle_setting = 0x10A;
    Offsets subtitle_show{ 0x13e20, 0x332c };
    Offsets hud_settings{ 0xa8, 0x151F8C };

    bool toggles[8];

    void toggleHUD();
    void toggleSubtitles();

   public:
    HUDHookHelper();
    void handleInput(const Gamepad& input);
  };
}  // namespace plugin
