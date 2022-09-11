#include "Hermes.h"

#include <MHW/memory.h>
#include <MHW/strings.h>
#include <gamepad.h>
#include <yaml-cpp/yaml.h>

#include <cmath>

#include "../model/AddressesConverter.h"

namespace plugin {
  using gamepad::Button;
  using gamepad::Buttons;
  using gamepad::Gamepad;
  using gamepad::justPressed;
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

      // idk what to do about it
      // NOLINTNEXTLINE(bugprone-narrowing-conversions,cppcoreguidelines-narrowing-conversions)
      float multiplier = pow(expBase, input.leftTriggerMagnitude) * direction;
      // std::cout << multiplier << std::endl;

      float walkSpeed = walk * multiplier;
      float runSpeed = run * multiplier;
      float dashSpeed = dash * multiplier;
      float sprintSpeed = sprint * multiplier;
      // float gravitySpeed = gravity * multiplier;

      writeMem(addresses.pl_params, walkSpeedOffset, walkSpeed);
      writeMem(addresses.pl_params, runSpeedOffset, runSpeed);
      writeMem(addresses.pl_params, dashSpeedOffset, dashSpeed);
      writeMem(addresses.pl_params, sprintSpeedOffset, sprintSpeed);
      // auto gravityAddr = writeMem(addresses.pl_params, gravitySpeedOffset, gravitySpeed);
    }
  }
}  // namespace plugin
