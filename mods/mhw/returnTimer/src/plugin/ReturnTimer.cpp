#include "ReturnTimer.h"

#include <MHW/memory.h>
#include <MHW/strings.h>
#include <yaml-cpp/yaml.h>

#include <cstdio>

#include "../model/AddressesConverter.h"

namespace plugin {

  using MHW::addressFile;
  using MHW::readMem;
  using stuff::types::Offsets;

  using namespace gamepad;

  ReturnTimer::ReturnTimer() {
    addresses = YAML::LoadFile(MHW::getFilePath(addressFile)).as<Addresses>();
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

  void ReturnTimer::addSeconds(float secs, float* timerAddr) const {
    *timerAddr -= 60 * secs;
    printf("Adding %.4fs: %.4f\n", secs, timerCurrent);
  }

  void ReturnTimer::freezeTimer(float* timerAddr) const {
    *timerAddr = frozenTime;
  }

  void ReturnTimer::toggleFreezeTimer(const float* timerAddr) {
    frozenTime = *timerAddr;
    freezeTime ^= true;
    printf("Freeze timer %s at %.4fs\n", (freezeTime ? "on" : "off"), frozenTime);
  }
  void ReturnTimer::endTimer(float* timerAddr) const {
    *timerAddr = timerMax;
    printf("Ending time: %f\n", timerCurrent);
  }

  tuple<float*, bool> ReturnTimer::readTimer() {
    readMem(addresses.session_quest, timerMaxOffset, timerMax);
    auto* timerAddr = (float*)readMem(addresses.session_quest, timerCurrentOffset, timerCurrent);
    return { timerAddr, ((timerMax > 0.0f) && (timerCurrent > 0.0f)) };
  }
}  // namespace plugin
