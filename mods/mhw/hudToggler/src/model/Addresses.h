#pragma once

#include <MHW/addy.h>
#include <types/address.h>

namespace model {
  using stuff::types::Pointer;

  class Addresses : public MHW::Addy {
   public:
    Pointer display_options;
    Pointer save_data;
  };
}  // namespace model
