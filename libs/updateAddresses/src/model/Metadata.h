#pragma once

#include <map>
#include <string>

#include "AOB.h"

namespace model {
  using std::map;
  using std::string;

  struct Metadata {
    map<string, AOB> basePointers;
    map<string, AOB> functions;
  };
}  // namespace model
