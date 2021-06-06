#pragma once

#include "types/address.h"
#pragma comment(lib, "stuff.lib")

using stuff::types::Pointer;

namespace MHW {
  class Addy {
   public:
    Pointer zone;

   protected:
    int getZoneID();
  };
}  // namespace MHW
