#include "addy.h"

#include "memory.h"

namespace MHW {
  int Addy::getZoneID() {
    int zoneID;
    MHW::readMem(zone, 0xaed0, zoneID);
    return zoneID;
  }
}  // namespace MHW
