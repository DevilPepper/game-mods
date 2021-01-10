#pragma once

#include "addy/addy.h"

namespace MHW {
  class IHook {
   public:
    Addy addresses;

   protected:
    IHook();
    static const intptr_t mhw = 0x140000000;
  };
}  // namespace MHW
