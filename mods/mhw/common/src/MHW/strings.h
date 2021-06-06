#pragma once

#include <format>
#include <string_view>

namespace MHW {
  constexpr std::string_view pathFormat = "nativePC/plugins/config/{}";
  constexpr std::string_view addressFile = "addresses.yaml";

  std::string getFilePath(std::string_view fileName) {
    return std::format(pathFormat, fileName);
  }
}  // namespace MHW
