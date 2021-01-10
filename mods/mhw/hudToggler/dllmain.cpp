// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>

#include "loader.h"
#pragma comment(lib, "loader.lib")

#include "stuff.h"
#pragma comment(lib, "stuff.lib")

#include "gamepad.h"
#pragma comment(lib, "GamepadHook.lib")

using loader::DEBUG;
using loader::LOG;
using std::string;
using std::vector;
using stuff::json::parseHexString;
using stuff::json::parseHexStrings;
using stuff::memory::readMem;
using stuff::memory::writeMem;

using namespace stuff::functions;
using namespace gamepad;

Button HUDToggle = Button::L1;
Button SubtitlesToggle = Button::Select;

intptr_t mhw = 0x140000000;

vector<intptr_t> subtitle_setting;
vector<intptr_t> subtitle_show;
vector<intptr_t> hud_settings;

bool toggles[8];

void loadAddresses() {
  auto addys = stuff::json::loadAddresses();
  subtitle_setting = parseHexStrings(addys["subtitle_setting"]);
  subtitle_show = parseHexStrings(addys["subtitle_show"]);
  hud_settings = parseHexStrings(addys["hud_settings"]);
}

void loadConfig() {
  // TODO: get this tf outta here
  // clang-format off
  vector<string> toggleStr{
    "Player Info",
    "Partner Info",
    "Scoutfly Notifications",
    "Minimap",
    "Large Monster Icon",
    "Button Guide",
    "Objectives",
    "Slinger Display",
    "Item Bar"
  };
  // clang-format on
  auto settings = stuff::json::loadConfig("HUD_toggles.json");
  for (int i = 0; i < 8; i++) {
    toggles[i] = settings[toggleStr[i]].get<bool>();
  }
}

void toggleSubtitles() {
  bool subs_setting;
  readMem(mhw, subtitle_setting, subs_setting);
  subs_setting ^= true;
  writeMem(mhw, subtitle_setting, subs_setting);

  bool subs_show;
  readMem(mhw, subtitle_show, subs_show);
  subs_show ^= true;
  writeMem(mhw, subtitle_show, subs_show);
}

void toggleHUD() {
  long long hud;
  auto hudAddr = readMem(mhw, hud_settings, hud);
  LOG(DEBUG) << std::hex << "Before @ 0x" << hudAddr << ": " << hud;
  hud ^= *reinterpret_cast<long long*>(toggles);
  writeMem(mhw, hud_settings, hud);
  LOG(DEBUG) << std::hex << "After @ 0x" << hudAddr << ": " << hud;
}

void callback(const Gamepad& gamepad) {
  if (justPressed(gamepad, Buttons[SubtitlesToggle])) {
    LOG(DEBUG) << std::hex << "Toggle Subtitles";
    toggleSubtitles();
  }
  if (justPressed(gamepad, Buttons[HUDToggle]) || justReleased(gamepad, Buttons[HUDToggle])) {
    LOG(DEBUG) << std::hex << "Toggle HUD";
    toggleHUD();
  }
  return;
}

void hookem() {
  gamepad::GetDispatcher().registerCallback(&callback);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
      loadAddresses();
      loadConfig();
      hookem();
      break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}
