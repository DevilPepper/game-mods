#pragma once

#include <string>

#include "gamepad.h"
#pragma comment(lib, "GamepadLib.lib")

#include "hooky/IHook.h"

using std::string;

class Hermes : public MHW::IHook {
 private:
  const string settings = "TheFlash.json";
  intptr_t walkSpeedOffset = 0x940;
  intptr_t runSpeedOffset = 0x980;
  intptr_t dashSpeedOffset = 0x9b0;

  int expBase;
  float walk = 1.12;
  float run = 1;
  float dash = 1.20;

 public:
  Hermes();
  void handleInput(const gamepad::Gamepad& input);
};
