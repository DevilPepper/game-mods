#pragma once

#include <thread>

namespace dll {
  void initSystemMessages();
  bool LoadAllPluginDlls(void* memModule);
  void watch(std::stop_token token);
}  // namespace dll
