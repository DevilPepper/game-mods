#pragma once

#include <string>

#include "gamepad.h"
#pragma comment(lib, "GamepadLib.lib")

#include "hooky/IHook.h"

using std::string;

class Counter : public MHW::IHook {
 public:
  Counter();
  void handleInput(const gamepad::Gamepad& input);
};
