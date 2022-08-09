#include "HUDHookHelper.h"

#include <MHW/strings.h>
#include <yaml-cpp/yaml.h>

#include "../model/AddressesConverter.h"
#include "strings.h"

namespace plugin {
  using MHW::addressFile;
  using namespace gamepad;

  HUDHookHelper::HUDHookHelper() {
    addresses = YAML::LoadFile(MHW::getFilePath(addressFile)).as<Addresses>();
    auto json = YAML::LoadFile(MHW::getFilePath(settings));
    for (int i = 0; i < 8; i++) {
      toggles[i] = json[toggleSettings[i]].as<bool>();
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
}  // namespace plugin
