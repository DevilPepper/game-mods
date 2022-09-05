#include "ToggleSubtitles.h"

#include <MHW/strings.h>
#include <yaml-cpp/yaml.h>

#include "../model/AddressesConverter.h"

namespace plugin {
  using MHW::addressFile;
  using namespace gamepad;

  ToggleSubtitles::ToggleSubtitles() {
    addresses = YAML::LoadFile(MHW::getFilePath(addressFile)).as<Addresses>();
  }

  void ToggleSubtitles::handleInput(const Gamepad& input) {
    if (justPressed(input, Buttons[SubtitlesToggle])) {
      toggleSubtitles();
    }
    return;
  }
}  // namespace plugin
