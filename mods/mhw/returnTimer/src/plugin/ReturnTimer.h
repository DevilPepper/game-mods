#pragma once

#include <tuple>

#include "gamepad.h"
#pragma comment(lib, "GamepadLib.lib")

#include "plugin/IPlugin.h"

using std::tuple;

class ReturnTimer : public MHW::IPlugin {
 private:
  intptr_t session_quest;
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
  void handleInput(const gamepad::Gamepad& input);
};
