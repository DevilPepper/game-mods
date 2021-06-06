#include "LockOn2MapPin.h"

#include <MHW/memory.h>
#include <MHW/strings.h>
#include <loader.h>
#include <yaml-cpp/yaml.h>

#include <algorithm>

#include "../model/AddressesConverter.h"

using loader::DEBUG;
using loader::LOG;
using MHW::addressFile;
using MHW::readMem;

LockOn2MapPin::LockOn2MapPin() {
  addresses = YAML::LoadFile(MHW::getFilePath(addressFile)).as<Addresses>();
}

void LockOn2MapPin::updatePin() {
  int idx = -1;
  auto lockOnAddr = readMem(addresses.quest_manager, lockOnOffsets, idx);
  LOG(DEBUG) << std::hex << "lockOn @ 0x" << lockOnAddr << ": " << idx;

  uintptr_t p0 = 0;
  auto unknownAddr = readMem(addresses.display_options, unknown, p0);
  LOG(DEBUG) << std::hex << "p0 @ 0x" << unknownAddr << ": " << p0;

  uintptr_t monster = 0;
  if (idx != -1) {
    int nMonsters = -1;
    auto numMonstersAddr = readMem(addresses.quest_manager, numMonsters, nMonsters);
    LOG(DEBUG) << std::hex << "numMonsters @ 0x" << numMonstersAddr << ": " << nMonsters;

    if (nMonsters > 0) {
      vector<uintptr_t> monsters;
      nMonsters--;
      for (int i = 0; i <= nMonsters; i++) {
        auto offset = (nMonsters - i) * 8;
        monster_i[1] = offset;
        auto monsterAddr = readMem(addresses.monsters, monster_i, monster);
        LOG(DEBUG) << std::hex << "monster found @ 0x" << monsterAddr << ": " << monster;
        monsters.push_back(monster);
      }

      // filter out dead or captured monsters that haven't despawned
      vector<uintptr_t> monstersOnTheLoose;
      std::copy_if(monsters.begin(),
                   monsters.end(),
                   std::back_inserter(monstersOnTheLoose),
                   [this](uintptr_t m) { return isOnTheLoose(m); });

      lockOnAddr -= 0x19F8;
      auto realIdx = getRealIndex(lockOnAddr, idx);
      auto realIdxArr = getRealIndexArray(lockOnAddr);

      pinMap(p0, monstersOnTheLoose[realIdxArr[realIdx]], 1);
    }
  } else {
    auto nonZeroAddr = readMem(addresses.pin_params, nonZero, monster);
    LOG(DEBUG) << std::hex << "non-zero @ 0x" << nonZeroAddr << ": " << monster;

    if (monster != 0) {
      auto pinnedMonsterAddr = readMem(addresses.pin_params, pinnedMonster, monster);
      LOG(DEBUG) << std::hex << "pinned monster @ 0x" << pinnedMonsterAddr << ": " << monster;
      pinMap(p0, monster, 1);
    }
  }
}
