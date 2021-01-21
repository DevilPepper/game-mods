#pragma once

#include "addy/addy.h"
#pragma comment(lib, "stuff.lib")

using namespace stuff;

namespace MHW {
  class IPlugin {
   public:
    addy::Addy addresses;

   protected:
    IPlugin();
    int getZoneID();
  };
}  // namespace MHW
