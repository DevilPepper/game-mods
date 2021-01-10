#include "stuff.h"
#pragma comment(lib, "stuff.lib")

#include "loader.h"
#pragma comment(lib, "loader.lib")

#include "LockOn2MapPin.h"

using namespace stuff::memory;

using loader::DEBUG;
using loader::LOG;

void LockOn2MapPin::pinMap(uintptr_t unknown, uintptr_t target, char isMonster) {
  addresses.getPinMapFunction()(unknown, target, isMonster, 0);
}

bool LockOn2MapPin::isOnTheLoose(intptr_t monsterAddr) {
  // Shameless copy and paste from Hunter Pie
  monsterAddr += 0x61C8;
  int actionId = *(int*)(monsterAddr + 0xB0);

  LOG(DEBUG) << std::hex << "actionId @ 0x" << (monsterAddr + 0xB0) << ": " << actionId;

  // clang-format off
  vector<intptr_t> monsterAction{
    monsterAddr + (2 * 8) + 0x68,
    (intptr_t)actionId * 8,
    0,
    0x20
  };
  // clang-format on

  intptr_t actionPtr = NULL;
  auto actionAddr = readMem(0, monsterAction, actionPtr);
  LOG(DEBUG) << std::hex << "monster action @ 0x" << actionAddr << ": " << actionPtr;

  auto offset = *(unsigned int*)(actionPtr + 3);
  LOG(DEBUG) << std::hex << "action offset @ 0x" << (actionPtr + 3) << ": " << offset;

  vector<intptr_t> actionRef{ actionPtr + offset + 7 + 8, 0 };

  auto strAddr = (char*)followPointers(0, actionRef);
  string action(strAddr);

  LOG(DEBUG) << std::hex << "action string @ 0x" << strAddr << ": " << action;

  // clang-format off
  return action.find("Capture") == string::npos
      && (action.find("Die")    == string::npos || action.find("DieSleep") != string::npos)
      && (action.find("Dead")   == string::npos || action.find("Deadly") != string::npos);
  // clang-format on
}

int LockOn2MapPin::getRealIndex(intptr_t address, int idx) {
  address -= 0x19F8;
  return *(int*)(address + ((intptr_t)idx * 8));
}
