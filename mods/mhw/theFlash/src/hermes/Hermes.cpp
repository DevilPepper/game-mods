#include "Hermes.h"

#include <math.h>

#include "MHW-deps.h"
#pragma comment(lib, "mhw-common.lib")

using loader::DEBUG;
using loader::LOG;
using stuff::addy::Offsets;
using stuff::memory::writeMem;

using namespace gamepad;

Hermes::Hermes() : MHW::IHook() {}

void Hermes::handleInput(const Gamepad& input) {
  if (pressing(input, Buttons[Button::R2]) || justReleased(input, Buttons[Button::R2])) {
    auto multiplier = pow(10, input.rightTriggerMagnitude);

    float walkSpeed = walk * multiplier;
    float runSpeed = run * multiplier;
    float dashSpeed = dash * multiplier;

    auto speedBase = addresses.get<intptr_t>("pl_params");
    auto walkAddr = writeMem(speedBase, walkSpeedOffset, walkSpeed);
    auto runAddr = writeMem(speedBase, runSpeedOffset, runSpeed);
    auto dashAddr = writeMem(speedBase, dashSpeedOffset, dashSpeed);

    if (multiplier == 1) {
      LOG(DEBUG) << std::hex << "Wrote " << walkSpeed << " @ 0x" << walkAddr;
      LOG(DEBUG) << std::hex << "Wrote " << runSpeed << " @ 0x" << runAddr;
      LOG(DEBUG) << std::hex << "Wrote " << dashSpeed << " @ 0x" << dashAddr;
    }
  }
}
