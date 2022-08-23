#include <memory/memory.h>
#include <types/address.h>

#include <format>
// #include <iostream>
#include <string_view>

#include "LockOn2MapPin.h"

namespace plugin {
  // using std::cout;
  using std::string_view;
  using stuff::memory::readMem;

  // Fourth param is always 0, so we're omitting it with this helper
  // targetType is always 1 for monster
  void LockOn2MapPin::pinMap(int64_t unknown, int64_t target, int64_t targetType) {
    addresses.fnPinMap(unknown, target, targetType, 0);
  }

  bool LockOn2MapPin::isOnTheLoose(Pointer monsterAddr) {
    // Shameless copy and paste from Hunter Pie
    monsterAddr += 0x61C8;
    int actionId = *(int*)(monsterAddr + 0xB0);

    // cout << std::format("actionId @ {:#010x}: {}", (monsterAddr + 0xB0), actionId);

    auto monsterActionBase = monsterAddr + (2 * 8) + 0x68;

    // clang-format off
  Offsets monsterAction{
    actionId * 8,
    0,
    0x20
  };
    // clang-format on

    Pointer actionPtr = NULL;
    auto actionAddr = readMem(monsterActionBase, monsterAction, actionPtr);
    // cout << std::format("monster action @ {:#010x}: {:#010x}", actionAddr, actionPtr);

    auto offset = *(unsigned int*)(actionPtr + 3);
    // cout << std::format("action offset @ {:#010x}: {:#010x}", (actionPtr + 3), offset);

    auto strAddr = (char**)(actionPtr + offset + 7 + 8);
    string_view action(*strAddr);

    // cout << std::format("action string @ {:#010x}: {}", (Pointer)strAddr, action);

    return isOnTheLoose(action);
  }

  bool LockOn2MapPin::isOnTheLoose(std::string_view action) {
    // clang-format off
  return action.find("Capture") == string_view::npos
      && (action.find("Die")    == string_view::npos || action.find("DieSleep") != string_view::npos)
      && (action.find("Dead")   == string_view::npos || action.find("Deadly")   != string_view::npos);
    // clang-format on
  }

  int LockOn2MapPin::getRealIndex(Pointer address, int idx) {
    return *(int*)(address + (idx * 8));
  }

  int* LockOn2MapPin::getRealIndexArray(Pointer address) {
    address += 0x6C;
    return (int*)address;
  }
}  // namespace plugin
