#include "Counter.h"

#include "MHW-deps.h"
#include "MHW.h"
#pragma comment(lib, "mhw-common.lib")

using loader::DEBUG;
using loader::LOG;
using stuff::addy::Offsets;
using stuff::memory::writeMem;

using namespace gamepad;

Counter::Counter() : MHW::IHook() {}

void Counter::handleInput(const Gamepad& input) {}
