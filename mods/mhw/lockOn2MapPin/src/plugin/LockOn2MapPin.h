#pragma once

#include <Windows.h>
#include <types/address.h>

#include <string_view>

#include "../model/Addresses.h"

namespace plugin {
  using model::Addresses;
  using stuff::types::Offsets;
  using stuff::types::Pointer;

  class LockOn2MapPin {
   private:
    intptr_t nonZero = 0x128;
    intptr_t pinnedMonster = 0x148;
    intptr_t unknown = 0x13FA0;
    Offsets monster_i{ 0x698, 0, 0x138 };
    Offsets lockOnOffsets{ 0x50, 0x80, 0x80, -0x7C };
    Offsets numMonsters{ 0x50, 0x80, 0x80, 0x120, 0x958 };

    void pinMap(uintptr_t unknown, uintptr_t target, char isMonster);
    bool isOnTheLoose(Pointer monsterAddr);
    bool isOnTheLoose(std::string_view action);
    int getRealIndex(Pointer address, int idx);
    int* getRealIndexArray(Pointer address);

   public:
    Addresses addresses;
    LockOn2MapPin();
    void updatePin();
  };
}  // namespace plugin
