#pragma once

#include <array>
#include <string_view>

namespace plugin {
  constexpr std::string_view settings = "HUD_toggles.json";

  // clang-format off
  constexpr std::array<std::string_view, 9> toggleSettings {
    "Player Info",
    "Partner Info",
    "Scoutfly Notifications",
    "Minimap",
    "Large Monster Icon",
    "Button Guide",
    "Objectives",
    "Slinger Display",
    // TODO: This isn't a bug??
    "Item Bar",
  };
  // clang-format on
}  // namespace plugin
