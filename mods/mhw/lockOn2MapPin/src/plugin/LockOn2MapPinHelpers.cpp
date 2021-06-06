#include <loader.h>
#include <memory/memory.h>

#include <string_view>

#include "LockOn2MapPin.h"

using loader::DEBUG;
using loader::LOG;
using std::string_view;
using stuff::memory::readMem;

void LockOn2MapPin::pinMap(uintptr_t unknown, uintptr_t target, char isMonster) {
  addresses.fnPinMap(unknown, target, isMonster, 0);
}

bool LockOn2MapPin::isOnTheLoose(intptr_t monsterAddr) {
  // Shameless copy and paste from Hunter Pie
  monsterAddr += 0x61C8;
  int actionId = *(int*)(monsterAddr + 0xB0);

  LOG(DEBUG) << std::hex << "actionId @ 0x" << (monsterAddr + 0xB0) << ": " << actionId;

  auto monsterActionBase = monsterAddr + (2 * 8) + 0x68;

  // clang-format off
  vector<intptr_t> monsterAction{
    (intptr_t)actionId * 8,
    0,
    0x20
  };
  // clang-format on

  intptr_t actionPtr = NULL;
  auto actionAddr = readMem(monsterActionBase, monsterAction, actionPtr);
  LOG(DEBUG) << std::hex << "monster action @ 0x" << actionAddr << ": " << actionPtr;

  auto offset = *(unsigned int*)(actionPtr + 3);
  LOG(DEBUG) << std::hex << "action offset @ 0x" << (actionPtr + 3) << ": " << offset;

  auto strAddr = (char**)(actionPtr + offset + 7 + 8);
  // vector<intptr_t> actionRef{ actionPtr + offset + 7 + 8, 0 };

  // auto strAddr = (char*)followPointers(0, actionRef);
  string_view action(*strAddr);

  LOG(DEBUG) << std::hex << "action string @ 0x" << strAddr << ": " << action;

  // clang-format off
  return action.find("Capture") == string_view::npos
      && (action.find("Die")    == string_view::npos || action.find("DieSleep") != string_view::npos)
      && (action.find("Dead")   == string_view::npos || action.find("Deadly")   != string_view::npos);
  // clang-format on
}

int LockOn2MapPin::getRealIndex(intptr_t address, int idx) {
  return *(int*)(address + ((intptr_t)idx * 8));
}

int* LockOn2MapPin::getRealIndexArray(intptr_t address) {
  address += 0x6C;
  return (int*)address;
}
