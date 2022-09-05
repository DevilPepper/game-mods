#pragma once

#include <unordered_map>
#include <string>

#include "AOB.h"

namespace model {
  using std::unordered_map;
  using std::string;

  struct Metadata {
    unordered_map<string, AOB> basePointers;
    unordered_map<string, AOB> functions;
  };
}  // namespace model
