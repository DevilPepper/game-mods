#pragma once

#include "addy/addy.h"

namespace MHW {
  class IHook {
   public:
    Addy addresses;

   protected:
    IHook();
  };
}  // namespace MHW
