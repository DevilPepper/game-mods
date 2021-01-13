#include "HUDHookHelper.h"

#include <string>

#include "MHW.h"
#pragma comment(lib, "mhw-common.lib")

using std::string;

HUDHookHelper::HUDHookHelper() : MHW::IHook() {
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
  auto json = MHW::loadConfig(settings);
  for (int i = 0; i < 8; i++) {
    toggles[i] = json[toggleStr[i]].get<bool>();
  }
}

void HUDHookHelper::handleInput(const Gamepad& input) {
  if (justPressed(input, Buttons[SubtitlesToggle])) {
    toggleSubtitles();
  }
  if (justPressed(input, Buttons[HUDToggle]) || justReleased(input, Buttons[HUDToggle])) {
    toggleHUD();
  }
  return;
}
