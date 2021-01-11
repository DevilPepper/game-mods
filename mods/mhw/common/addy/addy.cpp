#include "addy.h"

#include "stuff.h"
#pragma comment(lib, "stuff.lib")

namespace MHW {

  Addy::Addy() : offsets(map<string, vector<intptr_t>>()), address(map<string, intptr_t>()) {
    json = stuff::json::loadAddresses();
  }

}  // namespace MHW
