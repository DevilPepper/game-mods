#include "IPlugin.h"

#include <string>

#include "memory/memory.h"
#pragma comment(lib, "stuff.lib")

using stuff::addy::Pointer;
using stuff::memory::readMem;

namespace MHW {
  IPlugin::IPlugin() : addresses(addy::Addy()), sinker(hook::Line()) {}

  int IPlugin::getZoneID() {
    int zoneID;
    readMem(addresses.get<Pointer>("zone"), 0xaed0, zoneID);
    return zoneID;
  }
}  // namespace MHW

intptr_t stuff::memory::exeBase = 0x140000000;

#ifdef STUFF_PLUGIN
std::string stuff::addy::getAddressFilePath() {
  return "nativePC/plugins/config/addresses.json";
}
#endif
