#pragma once

#include "addy/addy.h"
#pragma comment(lib, "stuff.lib")

using stuff::addy::Addy;

namespace MHW {
  class IHook {
   public:
    Addy addresses;

   protected:
    IHook();
    int getZoneID();
  };
}  // namespace MHW
