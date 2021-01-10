#pragma once

#include <string>

#include "gamepad.h"
#pragma comment(lib, "GamepadHook.lib")

#include "hooky/IHook.h"

using namespace gamepad;
using std::string;

class LockOn2MapPin : public MHW::IHook {
 private:
  vector<intptr_t> monster_i;

  void pinMap(uintptr_t unknown, uintptr_t target, char isMonster);
  bool isOnTheLoose(intptr_t monsterAddr);
  int getRealIndex(intptr_t address, int idx);

 public:
  LockOn2MapPin();
  void updatePin();
};
