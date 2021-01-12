#include <iomanip>

#include "stuff.h"
#pragma comment(lib, "stuff.lib")

#include "loader.h"
#pragma comment(lib, "loader.lib")

#include "HUDHookHelper.h"

using stuff::memory::readMem;
using stuff::memory::writeMem;

using loader::DEBUG;
using loader::LOG;

void HUDHookHelper::toggleSubtitles() {
  bool subs_setting;
  bool subs_show;
  auto subsSettingsAddr =
      readMem(addresses.get<intptr_t>("save_data"), subtitle_setting, subs_setting);
  auto subsShowAddr = readMem(addresses.get<intptr_t>("display_options"), subtitle_show, subs_show);
  // clang-format off
  LOG(DEBUG) << std::hex << std::boolalpha << "Toggle Subtitles... "
             << "Before @ 0x" << subsSettingsAddr << ": " << subs_setting
             << " | @ 0x" << subsShowAddr << ": " << subs_show;
  // clang-format on

  subs_setting ^= true;
  subs_show ^= true;
  writeMem(addresses.get<intptr_t>("save_data"), subtitle_setting, subs_setting);
  writeMem(addresses.get<intptr_t>("display_options"), subtitle_show, subs_show);
  // clang-format off
  LOG(DEBUG) << std::hex << std::boolalpha << "Toggle Subtitles... "
             << "After @ 0x" << subsSettingsAddr << ": " << subs_setting
             << " | @ 0x" << subsShowAddr << ": " << subs_show;
  // clang-format on
}

void HUDHookHelper::toggleHUD() {
  long long hud;
  auto hudAddr = readMem(addresses.get<intptr_t>("save_data"), hud_settings, hud);
  LOG(DEBUG) << std::hex << "Toggle HUD... Before @ 0x" << hudAddr << ": " << hud;
  hud ^= *reinterpret_cast<long long*>(toggles);
  writeMem(addresses.get<intptr_t>("save_data"), hud_settings, hud);
  LOG(DEBUG) << std::hex << "Toggle HUD... After @ 0x" << hudAddr << ": " << hud;
}
