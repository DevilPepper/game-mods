#pragma once

#include <string>

#include "gamepad.h"
#pragma comment(lib, "GamepadHook.lib")

#include "hooky/IHook.h"

using namespace gamepad;
using std::string;

class HUDHookHelper : public MHW::IHook {
 private:
  const string settings = "HUD_toggles.json";
  static const Button HUDToggle = Button::L1;
  static const Button SubtitlesToggle = Button::Select;

  bool toggles[8];

  void toggleHUD();
  void toggleSubtitles();

 public:
  HUDHookHelper();
  void handleInput(const Gamepad& input);
};
