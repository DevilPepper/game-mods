#pragma once

#include "addy/addy.h"
#include "hook/line.h"
#pragma comment(lib, "stuff.lib")

using namespace stuff;

namespace MHW {
  class IPlugin {
   public:
    addy::Addy addresses;
    hook::Line sinker;

   protected:
    IPlugin();
    int getZoneID();
  };
}  // namespace MHW
