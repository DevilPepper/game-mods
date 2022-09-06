#include "HUDHookHelper.h"

#include <MHW/strings.h>
#include <yaml-cpp/yaml.h>

#include "../model/AddressesConverter.h"
#include "strings.h"

namespace plugin {
  using MHW::addressFile;

  HUDHookHelper::HUDHookHelper() {
    addresses = YAML::LoadFile(MHW::getFilePath(addressFile)).as<Addresses>();
    auto json = YAML::LoadFile(MHW::getFilePath(settings));
    for (int i = 0; i < 8; i++) {
      toggles[i] = json[toggleSettings[i].data()].as<bool>();
    }
  }
}  // namespace plugin
