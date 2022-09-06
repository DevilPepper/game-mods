#pragma once

#include <MHW/addy.h>
#include <types/address.h>

namespace model {
  using stuff::types::Offsets;
  using stuff::types::Pointer;

  using InvokableConsumer = void (*)(uint64_t, uint64_t, int64_t, int64_t);

  class Addresses : public MHW::Addy {
   public:
    Pointer quest_manager;
    Pointer display_options;
    Pointer monsters;
    Pointer pin_params;

    InvokableConsumer fnPinMap;
    Pointer fnLockOnIncrement;
  };
}  // namespace model
