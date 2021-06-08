#pragma once

#include <string_view>

namespace plugin {
  constexpr std::string_view settings = "HUD_toggles.json";

  // clang-format off
  const char* toggleSettings[] = {
    "Player Info",
    "Partner Info",
    "Scoutfly Notifications",
    "Minimap",
    "Large Monster Icon",
    "Button Guide",
    "Objectives",
    "Slinger Display",
    "Item Bar"
  };
  // clang-format on
}  // namespace plugin
