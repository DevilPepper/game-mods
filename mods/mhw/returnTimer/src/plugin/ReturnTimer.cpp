#include "ReturnTimer.h"

#include <cstdio>

#include "MHW-deps.h"
#include "MHW.h"
#pragma comment(lib, "mhw-common.lib")

using stuff::addy::Offsets;
using stuff::memory::readMem;
using stuff::memory::writeMem;

using namespace gamepad;

ReturnTimer::ReturnTimer() : MHW::IPlugin() {
  session_quest = addresses.get<intptr_t>("session_quest");
}

void ReturnTimer::handleInput(const Gamepad& input) {
  auto [timerAddr, isEndOfQuest] = readTimer();
  if (isEndOfQuest) {
    if (freezeTime) {
      freezeTimer(timerAddr);
    }
    if (pressing(input, Buttons[Button::L1])) {
      if (justPressed(input, Buttons[Button::Triangle])) {
        addSeconds(10, timerAddr);
      } else if (justPressed(input, Buttons[Button::Circle])) {
        toggleFreezeTimer(timerAddr);
      } else if (justPressed(input, Buttons[Button::Cross])) {
        endTimer(timerAddr);
      }
    }
  }
}

void ReturnTimer::addSeconds(float secs, float* timerAddr) {
  *timerAddr -= 60 * secs;
  printf("Adding %.4fs: %.4f\n", secs, timerCurrent);
}

void ReturnTimer::freezeTimer(float* timerAddr) {
  *timerAddr = frozenTime;
}

void ReturnTimer::toggleFreezeTimer(float* timerAddr) {
  frozenTime = *timerAddr;
  freezeTime ^= true;
  printf("Freeze timer %s at %.4fs\n", (freezeTime ? "on" : "off"), frozenTime);
}
void ReturnTimer::endTimer(float* timerAddr) {
  *timerAddr = timerMax;
  printf("Ending time: %f\n", timerCurrent);
}

tuple<float*, bool> ReturnTimer::readTimer() {
  readMem(session_quest, timerMaxOffset, timerMax);
  auto timerAddr = (float*)readMem(session_quest, timerCurrentOffset, timerCurrent);
  return { timerAddr, ((timerMax > 0.0f) && (timerCurrent > 0.0f)) };
}
