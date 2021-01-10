#pragma once

#include <string>

#include "gamepad.h"
#pragma comment(lib, "GamepadHook.lib")

#include "hooky/IHook.h"

using namespace gamepad;
using std::string;

class HUDHookHelper : public MHW::IHook {
 private:
  static const string settings;
  static const Button HUDToggle = Button::L1;
  static const Button SubtitlesToggle = Button::Select;

  bool toggles[8];

  void toggleHUD();
  void toggleSubtitles();

 public:
  HUDHookHelper();
  void handleInput(const Gamepad& input);
};
