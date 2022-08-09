#pragma once

#include <types/address.h>
#include <types/ghidra.h>

#include <utility>

namespace plugin {
  using ghidra::types::byte;
  using stuff::types::Pointer;

  std::pair<byte*, byte*> getScanRange(Pointer base);
}  // namespace plugin
