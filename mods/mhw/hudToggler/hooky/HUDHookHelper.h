#pragma once

#include <Windows.h>

#include <string>
#include <vector>

#include "gamepad.h"
#pragma comment(lib, "GamepadLib.lib")

#include "hooky/IHook.h"

using namespace gamepad;
using std::string;
using std::vector;

class HUDHookHelper : public MHW::IHook {
 private:
  const string settings = "HUD_toggles.json";
  static const Button HUDToggle = Button::L1;
  static const Button SubtitlesToggle = Button::Select;

  intptr_t subtitle_setting = 0x10A;
  vector<intptr_t> subtitle_show{ 0x13e20, 0x332c };
  vector<intptr_t> hud_settings{ 0xa8, 0x151F8C };

  bool toggles[8];

  void toggleHUD();
  void toggleSubtitles();

 public:
  HUDHookHelper();
  void handleInput(const Gamepad& input);
};
