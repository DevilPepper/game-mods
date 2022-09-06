#include "LockOn2MapPin.h"

#include <MHW/memory.h>
#include <MHW/strings.h>
#include <yaml-cpp/yaml.h>

#include <algorithm>
#include <format>
#include <vector>
// #include <iostream>

#include "../model/AddressesConverter.h"

namespace plugin {
  using MHW::addressFile;
  using MHW::readMem;
  // using std::cout;
  using std::vector;

  LockOn2MapPin::LockOn2MapPin() {
    addresses = YAML::LoadFile(MHW::getFilePath(addressFile)).as<Addresses>();
  }

  void LockOn2MapPin::updatePin() {
    int idx = -1;
    auto lockOnAddr = readMem(addresses.quest_manager, lockOnOffsets, idx);

    uintptr_t p0 = 0;
    readMem(addresses.display_options, unknown, p0);

    uintptr_t monster = 0;
    if (idx != -1) {
      int nMonsters = -1;
      readMem(addresses.quest_manager, numMonsters, nMonsters);

      if (nMonsters > 0) {
        vector<uintptr_t> monsters;
        nMonsters--;
        for (int i = 0; i <= nMonsters; i++) {
          auto offset = (nMonsters - i) * 8;
          monster_i[1] = offset;
          readMem(addresses.monsters, monster_i, monster);
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
        auto *realIdxArr = getRealIndexArray(lockOnAddr);

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        pinMap(p0, monstersOnTheLoose[realIdxArr[realIdx]], 1);
      }
    } else {
      readMem(addresses.pin_params, nonZero, monster);

      if (monster != 0) {
        readMem(addresses.pin_params, pinnedMonster, monster);
        pinMap(p0, monster, 1);
      }
    }
  }
}  // namespace plugin
