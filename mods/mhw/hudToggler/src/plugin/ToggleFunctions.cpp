
#include <MHW/memory.h>

#include "HUDHookHelper.h"

namespace plugin {

  using MHW::mhwBase;
  using MHW::readMem;
  using MHW::writeMem;

  void HUDHookHelper::writeHUD() {
    // TODO: move to common lib and call it readMemSafe
    auto addy = *(intptr_t*)(mhwBase + addresses.display_options);
    if (addy == 0) {
      return;
    }
    addy = *(intptr_t*)(addy + 0x14300);
    if (addy == 0) {
      return;
    }

    auto isActive = *(bool*)(addy + 0x2900);
    if (wasActive ^ isActive) {
      wasActive = isActive;
      long long hud;
      readMem(addresses.save_data, hud_settings, hud);
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      auto mask = *reinterpret_cast<long long*>(toggles.data());

      hud &= ~mask;
      if (!isActive) {
        hud |= mask;
      }
      writeMem(addresses.save_data, hud_settings, hud);
    }
  }
}  // namespace plugin
