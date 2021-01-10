#include "addy.h"

#include "stuff.h"
#pragma comment(lib, "stuff.lib")

using stuff::json::parseHexString;
using stuff::json::parseHexStrings;

namespace MHW {

  Addy::Addy() {
    auto addys = stuff::json::loadAddresses();

    subtitleSettingOffsets = parseHexStrings(addys["subtitle_setting"]);
    subtitleShowOffsets = parseHexStrings(addys["subtitle_show"]);
    hudSettingsOffsets = parseHexStrings(addys["hud_settings"]);

    lockOnOffsets = parseHexStrings(addys["lockOnOffsets"]);
    unknownOffsets = parseHexStrings(addys["unknown"]);
    lastMonsterOffsets = parseHexStrings(addys["lastMonster"]);
    numMonstersOffsets = parseHexStrings(addys["numMonsters"]);
    nonZeroOffsets = parseHexStrings(addys["nonZero"]);
    pinnedMonsterOffsets = parseHexStrings(addys["pinnedMonsterPtr"]);

    lockOnIncrementAddress = parseHexString(addys["LockOnIncrement()"]);
    pinMapFunction = (PtrPtrCharCharConsumer)parseHexString(addys["PinMap()"]);
  }

  const vector<intptr_t>& Addy::getSubtitleSettingOffsets() {
    return subtitleSettingOffsets;
  }

  const vector<intptr_t>& Addy::getSubtitleShowOffsets() {
    return subtitleShowOffsets;
  }

  const vector<intptr_t>& Addy::getHudSettingsOffsets() {
    return hudSettingsOffsets;
  }

  const vector<intptr_t>& Addy::getLockOnOffsets() {
    return lockOnOffsets;
  }

  const vector<intptr_t>& Addy::getUnknownOffsets() {
    return unknownOffsets;
  }

  const vector<intptr_t>& Addy::getLastMonsterOffsets() {
    return lastMonsterOffsets;
  }

  const vector<intptr_t>& Addy::getNumMonstersOffsets() {
    return numMonstersOffsets;
  }

  const vector<intptr_t>& Addy::getNonZeroOffsets() {
    return nonZeroOffsets;
  }

  const vector<intptr_t>& Addy::getPinnedMonsterPtrOffsets() {
    return pinnedMonsterOffsets;
  }

  const intptr_t& Addy::getLockOnIncrementAddress() {
    return lockOnIncrementAddress;
  }

  const PtrPtrCharCharConsumer& Addy::getPinMapFunction() {
    return pinMapFunction;
  }

}  // namespace MHW
