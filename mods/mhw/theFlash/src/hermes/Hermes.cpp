#include "Hermes.h"

#include <math.h>

#include "loader.h"
#pragma comment(lib, "loader.lib")

#include "stuff.h"
#pragma comment(lib, "stuff.lib")

using loader::DEBUG;
using loader::LOG;
using MHW::Offsets;
using stuff::memory::writeMem;

using namespace gamepad;

Hermes::Hermes() : MHW::IHook() {}

void Hermes::handleInput(const Gamepad& input) {
  if (pressing(input, Buttons[Button::R2]) || justReleased(input, Buttons[Button::R2])) {
    auto multiplier = pow(10, input.rightTriggerMagnitude);

    float walkSpeed = walk * multiplier;
    float runSpeed = run * multiplier;
    float dashSpeed = dash * multiplier;

    auto walkAddr = writeMem(mhw, addresses.get<Offsets>("walkSpeed"), walkSpeed);
    auto runAddr = writeMem(mhw, addresses.get<Offsets>("runSpeed"), runSpeed);
    auto dashAddr = writeMem(mhw, addresses.get<Offsets>("dashSpeed"), dashSpeed);

    if (multiplier == 1) {
      LOG(DEBUG) << std::hex << "Wrote " << walkSpeed << " @ 0x" << walkAddr;
      LOG(DEBUG) << std::hex << "Wrote " << runSpeed << " @ 0x" << runAddr;
      LOG(DEBUG) << std::hex << "Wrote " << dashSpeed << " @ 0x" << dashAddr;
    }
  }
}
