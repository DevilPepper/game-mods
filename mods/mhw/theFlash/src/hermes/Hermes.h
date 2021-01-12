#pragma once

#include <string>

#include "gamepad.h"
#pragma comment(lib, "GamepadHook.lib")

#include "hooky/IHook.h"

using std::string;

class Hermes : public MHW::IHook {
 private:
  float walk = 1.12;
  float run = 1;
  float dash = 1.20;

 public:
  Hermes();
  void handleInput(const gamepad::Gamepad& input);
};
