#pragma once

#include <Windows.h>

#include <string>
#include <vector>

#include "gamepad.h"
#pragma comment(lib, "GamepadHook.lib")

#include "hooky/IHook.h"

using namespace gamepad;
using std::string;
using std::vector;

class LockOn2MapPin : public MHW::IHook {
 private:
  intptr_t nonZero = 0x128;
  intptr_t pinnedMonster = 0x148;
  intptr_t unknown = 0x13FA0;
  vector<intptr_t> monster_i{ 0x698, 0, 0x138 };
  vector<intptr_t> lockOnOffsets{ 0x50, 0x80, 0x80, -0x7C };
  vector<intptr_t> numMonsters{ 0x50, 0x80, 0x80, 0x120, 0x958 };

  void pinMap(uintptr_t unknown, uintptr_t target, char isMonster);
  bool isOnTheLoose(intptr_t monsterAddr);
  int getRealIndex(intptr_t address, int idx);

 public:
  LockOn2MapPin();
  void updatePin();
};
