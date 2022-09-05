#pragma once

#include <types/address.h>

namespace MHW {
  using stuff::types::Pointer;
  class Addy {
   public:
    Pointer zone;
    int getZoneID() const;
  };
}  // namespace MHW
