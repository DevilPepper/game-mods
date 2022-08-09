#pragma once

#include <types/address.h>

namespace model {
  using stuff::types::Pointer;

  struct BasePointer {
    Pointer address;
    Pointer source;
  };
}  // namespace model
