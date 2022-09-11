#include "ToggleSubtitles.h"

#include <MHW/strings.h>
#include <yaml-cpp/yaml.h>

#include "../model/AddressesConverter.h"

namespace plugin {
  using gamepad::Buttons;
  using gamepad::Gamepad;
  using gamepad::justPressed;
  using MHW::addressFile;

  ToggleSubtitles::ToggleSubtitles() {
    addresses = YAML::LoadFile(MHW::getFilePath(addressFile)).as<Addresses>();
  }

  void ToggleSubtitles::handleInput(const Gamepad& input) {
    if (justPressed(input, Buttons[SubtitlesToggle])) {
      toggleSubtitles();
    }
  }
}  // namespace plugin
