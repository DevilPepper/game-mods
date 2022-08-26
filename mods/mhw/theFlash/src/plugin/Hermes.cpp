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
      if (justPressed(input, Buttons[Button::L3])) {
        direction *= -1;
        // What is this?
        // std::cout << ((Producer)0x140f30030)() << std::endl;
      }

      auto multiplier = pow(expBase, input.leftTriggerMagnitude) * direction;
      // std::cout << multiplier << std::endl;

      float walkSpeed = walk * multiplier;
      float runSpeed = run * multiplier;
      float dashSpeed = dash * multiplier;
      float sprintSpeed = sprint * multiplier;
      // float gravitySpeed = gravity * multiplier;

      auto walkAddr = writeMem(addresses.pl_params, walkSpeedOffset, walkSpeed);
      auto runAddr = writeMem(addresses.pl_params, runSpeedOffset, runSpeed);
      auto dashAddr = writeMem(addresses.pl_params, dashSpeedOffset, dashSpeed);
      auto sprintAddr = writeMem(addresses.pl_params, sprintSpeedOffset, sprintSpeed);
      // auto gravityAddr = writeMem(addresses.pl_params, gravitySpeedOffset, gravitySpeed);
    }
  }
}  // namespace plugin
