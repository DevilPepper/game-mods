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
    intptr_t timerCurrentOffset = 0x13350;
    intptr_t timerMaxOffset = 0x13354;

    float timerCurrent = 0;
    float timerMax = 0;
    float frozenTime = 0;
    bool freezeTime = false;

    void addSeconds(float secs, float* timerAddr);
    void freezeTimer(float* timerAddr);
    void toggleFreezeTimer(float* timerAddr);
    void endTimer(float* timerAddr);
    tuple<float*, bool> readTimer();

   public:
    ReturnTimer();
    void handleInput(const Gamepad& input);
  };
}  // namespace plugin
