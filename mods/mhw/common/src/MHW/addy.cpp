#include "addy.h"

#include "memory.h"

namespace MHW {
  Addy::Addy() {}

  int Addy::getZoneID() {
    int zoneID;
    MHW::readMem(zone, 0xaed0, zoneID);
    return zoneID;
  }
}  // namespace MHW
