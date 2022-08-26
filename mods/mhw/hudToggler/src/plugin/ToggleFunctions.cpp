
#include <MHW/memory.h>

#include "HUDHookHelper.h"

namespace plugin {

  using MHW::readMem;
  using MHW::writeMem;

  void HUDHookHelper::toggleSubtitles() {
    bool subs_setting;
    bool subs_show;
    auto subsSettingsAddr = readMem(addresses.save_data, subtitle_setting, subs_setting);
    auto subsShowAddr = readMem(addresses.display_options, subtitle_show, subs_show);

    subs_setting ^= true;
    subs_show ^= true;
    writeMem(addresses.save_data, subtitle_setting, subs_setting);
    writeMem(addresses.display_options, subtitle_show, subs_show);
  }

  void HUDHookHelper::writeHUD(long long* hudStruct) {
    // TODO: how often does this get called?
    auto isActive = *(bool*)(hudStruct + 0x520);
    long long hud;
    auto hudAddr = readMem(addresses.save_data, hud_settings, hud);
    auto mask = *reinterpret_cast<long long*>(toggles);

    hud &= ~mask;
    if (!isActive) {
      hud |= mask;
    }
    writeMem(addresses.save_data, hud_settings, hud);
  }
}  // namespace plugin
