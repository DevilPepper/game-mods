#include "Hermes.h"

#include <MHW/memory.h>
#include <MHW/strings.h>
#include <math.h>
#include <yaml-cpp/yaml.h>

#include "../model/AddressesConverter.h"

namespace plugin {
  using MHW::addressFile;
  using MHW::writeMem;

  Hermes::Hermes() {
    expBase = YAML::LoadFile(MHW::getFilePath(settings))["maxSpeedMultiplier"].as<int>();
    addresses = YAML::LoadFile(MHW::getFilePath(addressFile)).as<Addresses>();
  }

  void Hermes::handleInput(const Gamepad& input) {
    if (addresses.getZoneID() != 0) {
      auto multiplier = pow(expBase, input.leftTriggerMagnitude);

      float walkSpeed = walk * multiplier;
      float runSpeed = run * multiplier;
      float dashSpeed = dash * multiplier;

      auto walkAddr = writeMem(addresses.pl_params, walkSpeedOffset, walkSpeed);
      auto runAddr = writeMem(addresses.pl_params, runSpeedOffset, runSpeed);
      auto dashAddr = writeMem(addresses.pl_params, dashSpeedOffset, dashSpeed);
    }
  }
}  // namespace plugin
