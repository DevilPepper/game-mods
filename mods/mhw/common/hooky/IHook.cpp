#include "IHook.h"

#include "memory/memory.h"
#pragma comment(lib, "stuff.lib")

namespace MHW {
  IHook::IHook() : addresses(Addy()) {}
}  // namespace MHW

intptr_t stuff::memory::exeBase = 0x140000000;
