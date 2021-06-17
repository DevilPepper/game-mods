#include "PEInfo.h"

#include <winnt.h>

#include <string_view>

namespace plugin {
  // https://stackoverflow.com/a/4316804
  std::pair<byte*, byte*> getScanRange(Pointer base) {
    auto headerOffset = *(int*)(base + 0x3c);
    auto NTHeader = (IMAGE_NT_HEADERS*)(base + headerOffset);
    auto sectionHeaders = (IMAGE_SECTION_HEADER*)(NTHeader + 1);

    std::string_view name;
    for (int i = 0; i < NTHeader->FileHeader.NumberOfSections; i++) {
      name = (char*)sectionHeaders[i].Name;
      if (name == ".text") {
        auto begin = base + sectionHeaders[i].VirtualAddress;
        auto end = begin + sectionHeaders[i].Misc.VirtualSize;
        return { (byte*)begin, (byte*)end };
      }
    }
    return {};
  }
}  // namespace plugin
