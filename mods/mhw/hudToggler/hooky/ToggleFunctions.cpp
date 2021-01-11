#include <iomanip>

#include "stuff.h"
#pragma comment(lib, "stuff.lib")

#include "loader.h"
#pragma comment(lib, "loader.lib")

#include "HUDHookHelper.h"

using MHW::Offsets;
using stuff::memory::readMem;
using stuff::memory::writeMem;

using loader::DEBUG;
using loader::LOG;

void HUDHookHelper::toggleSubtitles() {
  auto subtitle_setting = addresses.get<Offsets>("subtitle_setting");
  auto subtitle_show = addresses.get<Offsets>("subtitle_show");

  bool subs_setting;
  bool subs_show;
  auto subsSettingsAddr = readMem(mhw, subtitle_setting, subs_setting);
  auto subsShowAddr = readMem(mhw, subtitle_show, subs_show);
  // clang-format off
  LOG(DEBUG) << std::hex << std::boolalpha << "Toggle Subtitles... "
             << "Before @ 0x" << subsSettingsAddr << ": " << subs_setting
             << " | @ 0x" << subsShowAddr << ": " << subs_show;
  // clang-format on

  subs_setting ^= true;
  subs_show ^= true;
  writeMem(mhw, subtitle_setting, subs_setting);
  writeMem(mhw, subtitle_show, subs_show);
  // clang-format off
  LOG(DEBUG) << std::hex << std::boolalpha << "Toggle Subtitles... "
             << "After @ 0x" << subsSettingsAddr << ": " << subs_setting
             << " | @ 0x" << subsShowAddr << ": " << subs_show;
  // clang-format on
}

void HUDHookHelper::toggleHUD() {
  long long hud;
  auto hud_settings = addresses.get<Offsets>("hud_settings");
  auto hudAddr = readMem(mhw, hud_settings, hud);
  LOG(DEBUG) << std::hex << "Toggle HUD... Before @ 0x" << hudAddr << ": " << hud;
  hud ^= *reinterpret_cast<long long*>(toggles);
  writeMem(mhw, hud_settings, hud);
  LOG(DEBUG) << std::hex << "Toggle HUD... After @ 0x" << hudAddr << ": " << hud;
}
