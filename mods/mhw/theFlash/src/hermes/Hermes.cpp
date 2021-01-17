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
  if (getZoneID() != 0) {
    auto multiplier = pow(10, input.leftTriggerMagnitude);

    float walkSpeed = walk * multiplier;
    float runSpeed = run * multiplier;
    float dashSpeed = dash * multiplier;

    auto speedBase = addresses.get<intptr_t>("pl_params");
    auto walkAddr = writeMem(speedBase, walkSpeedOffset, walkSpeed);
    auto runAddr = writeMem(speedBase, runSpeedOffset, runSpeed);
    auto dashAddr = writeMem(speedBase, dashSpeedOffset, dashSpeed);
  }
}
