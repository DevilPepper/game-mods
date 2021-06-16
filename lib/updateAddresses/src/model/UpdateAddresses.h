#pragma once

#include <string>

namespace model {
  using std::string;
  struct UpdateAddresses {
    string addresses;
    string metadata;
    char trailingBytes;
  };
}  // namespace model
