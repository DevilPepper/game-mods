#pragma once

#include <format>
#include <string_view>

namespace MHW {
  constexpr std::string_view getFilePath(std::string_view fileName) {
    return std::format("nativePC/plugins/config/{}", fileName);
  }

  constexpr std::string_view addressFile = "addresses.yaml";
}  // namespace MHW
