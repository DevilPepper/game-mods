#pragma once

#include <types/address.h>

#include <unordered_map>
#include <string>

#include "BasePointer.h"

namespace model {
  using std::unordered_map;
  using std::string;

  struct Addresses {
    unordered_map<string, model::BasePointer> basePointers;
    unordered_map<string, stuff::types::Pointer> functions;
  };
}  // namespace model
