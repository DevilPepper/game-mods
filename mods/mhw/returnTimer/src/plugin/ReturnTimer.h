#pragma once

#include <gamepad.h>

#include <tuple>

#include "../model/Addresses.h"

namespace plugin {
  using gamepad::Gamepad;
  using model::Addresses;
  using std::tuple;

  class ReturnTimer {
   private:
    Addresses addresses;
    intptr_t timerCurrentOffset = 0x131a0;
    intptr_t timerMaxOffset = 0x131a4;

    float timerCurrent = 0;
    float timerMax = 0;
    float frozenTime = 0;
    bool freezeTime = false;

    void addSeconds(float secs, float* timerAddr) const;
    void freezeTimer(float* timerAddr) const;
    void toggleFreezeTimer(const float* timerAddr);
    void endTimer(float* timerAddr) const;
    tuple<float*, bool> readTimer();

   public:
    ReturnTimer();
    void handleInput(const Gamepad& input);
  };
}  // namespace plugin
