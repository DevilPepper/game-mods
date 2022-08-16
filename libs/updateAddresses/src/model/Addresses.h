#pragma once

#include <types/address.h>

#include <map>
#include <string>

#include "BasePointer.h"

namespace model {
  using std::map;
  using std::string;

  struct Addresses {
    map<string, model::BasePointer> basePointers;
    map<string, stuff::types::Pointer> functions;
  };
}  // namespace model
