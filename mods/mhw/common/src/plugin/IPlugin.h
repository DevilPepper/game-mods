#pragma once

#include <Windows.h>

#include <vector>

#include "addy/addy.h"
#pragma comment(lib, "stuff.lib")

using namespace stuff;

namespace MHW {
  class IPlugin {
   public:
    addy::Addy addresses;
    std::vector<intptr_t> targets;

   protected:
    IPlugin();
    int getZoneID();
  };
}  // namespace MHW
