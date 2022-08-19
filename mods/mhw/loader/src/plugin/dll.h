#pragma once

#include <thread>

namespace dll {
  void LoadAllPluginDlls(void* memModule);
  void watch(std::stop_token token);
}  // namespace dll
