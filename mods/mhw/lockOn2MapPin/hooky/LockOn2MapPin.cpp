#include "stuff.h"
#pragma comment(lib, "stuff.lib")

#include "loader.h"
#pragma comment(lib, "loader.lib")

#include "LockOn2MapPin.h"

using stuff::memory::readMem;

using loader::DEBUG;
using loader::LOG;

LockOn2MapPin::LockOn2MapPin() : MHW::IHook() {
  monster_i = addresses.getLastMonsterOffsets();
}

void LockOn2MapPin::updatePin() {
  int idx = -1;
  auto lockOnAddr = readMem(mhw, addresses.getLockOnOffsets(), idx);
  LOG(DEBUG) << std::hex << "lockOn @ 0x" << lockOnAddr << ": " << idx;

  uintptr_t p0 = 0;
  auto unknownAddr = readMem(mhw, addresses.getUnknownOffsets(), p0);
  LOG(DEBUG) << std::hex << "p0 @ 0x" << unknownAddr << ": " << p0;

  uintptr_t monster = 0;
  if (idx != -1) {
    int nMonsters = -1;
    auto numMonstersAddr = readMem(mhw, addresses.getNumMonstersOffsets(), nMonsters);
    LOG(DEBUG) << std::hex << "numMonsters @ 0x" << numMonstersAddr << ": " << nMonsters;

    if (nMonsters > 0) {
      vector<uintptr_t> monsters;
      nMonsters--;
      for (int i = 0; i <= nMonsters; i++) {
        auto offset = (nMonsters - i) * 8;
        monster_i[2] = offset;
        auto monsterAddr = readMem(mhw, monster_i, monster);
        LOG(DEBUG) << std::hex << "monster found @ 0x" << monsterAddr << ": " << monster;
        monsters.push_back(monster);
      }

      // filter out dead or captured monsters that haven't despawned
      vector<uintptr_t> monstersOnTheLoose;
      std::copy_if(monsters.begin(),
                   monsters.end(),
                   std::back_inserter(monstersOnTheLoose),
                   [this](uintptr_t m) { return isOnTheLoose(m); });

      pinMap(p0, monstersOnTheLoose[getRealIndex(lockOnAddr, idx)], 1);
    }
  } else {
    auto nonZeroAddr = readMem(mhw, addresses.getNonZeroOffsets(), monster);
    LOG(DEBUG) << std::hex << "non-zero @ 0x" << nonZeroAddr << ": " << monster;

    if (monster != 0) {
      auto pinnedMonsterAddr = readMem(mhw, addresses.getPinnedMonsterPtrOffsets(), monster);
      LOG(DEBUG) << std::hex << "pinned monster @ 0x" << pinnedMonsterAddr << ": " << monster;
      pinMap(p0, monster, 1);
    }
  }
}
