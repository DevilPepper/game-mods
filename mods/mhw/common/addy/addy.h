#pragma once

#include <windows.h>

#include <vector>

#include "function/function.h"

using namespace stuff::functions;
using std::vector;

namespace MHW {
  class Addy {
   private:
    vector<intptr_t> subtitleSettingOffsets;
    vector<intptr_t> subtitleShowOffsets;
    vector<intptr_t> hudSettingsOffsets;

    vector<intptr_t> lockOnOffsets;
    vector<intptr_t> unknownOffsets;
    vector<intptr_t> lastMonsterOffsets;
    vector<intptr_t> numMonstersOffsets;
    vector<intptr_t> nonZeroOffsets;
    vector<intptr_t> pinnedMonsterOffsets;

    intptr_t lockOnIncrementAddress;
    PtrPtrCharCharConsumer pinMapFunction;

   public:
    Addy();

    const vector<intptr_t>& getSubtitleSettingOffsets();
    const vector<intptr_t>& getSubtitleShowOffsets();
    const vector<intptr_t>& getHudSettingsOffsets();

    const vector<intptr_t>& getLockOnOffsets();
    const vector<intptr_t>& getUnknownOffsets();
    const vector<intptr_t>& getLastMonsterOffsets();
    const vector<intptr_t>& getNumMonstersOffsets();
    const vector<intptr_t>& getNonZeroOffsets();
    const vector<intptr_t>& getPinnedMonsterPtrOffsets();

    const intptr_t& getLockOnIncrementAddress();
    const PtrPtrCharCharConsumer& getPinMapFunction();
  };

}  // namespace MHW
