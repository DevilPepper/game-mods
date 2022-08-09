#include "AddressFacade.h"

#include <Windows.h>
#include <aob/PatternSearch.h>
#include <ctype.h>
#include <yaml-cpp/yaml.h>

#include <string>

#include "../converters/BasePointerConverter.h"
#include "../converters/MetadataConverter.h"
#include "../converters/UpdateAddressesConverter.h"
#include "../model/BasePointer.h"
#include "PEInfo.h"

namespace plugin {
  using std::string;
  using stuff::aob::PatternSearch::findInMemory;

  AddressFacade::AddressFacade() {
    exeBase = (Pointer)GetModuleHandle(NULL);
    config = YAML::LoadFile("UpdateAddresses.yaml").as<UpdateAddresses>();
    metadata = YAML::LoadFile(config.metadata).as<Metadata>();
  }
  bool AddressFacade::isGood() {
    bool allGood = true;
    auto yaml = YAML::LoadFile(config.addresses);

    for (const auto& it : yaml["basePointers"]) {
      auto info = it.second.as<model::BasePointer>();
      // Disabled clang-format because it prefers to put the entire expression in a new line
      // instead of AlignOperands...
      // clang-format off
      auto constantPtr = info.source
                       + metadata.basePointers[it.first.as<string>()].offset
                       + exeBase;
      // clang-format on

      allGood &= (info.address == (constantPtr + 4 + (*(int*)constantPtr) - exeBase));
      if (!allGood) {
        break;
      }
    }

    for (const auto& it : yaml["functions"]) {
      // Disabled clang-format because it prefers to put the entire expression in a new line
      // instead of AlignOperands...
      // clang-format off
      auto addy = it.second.as<Pointer>()
                + exeBase
                - metadata.functions[it.first.as<string>()].offset;
      // clang-format on

      string_view aob = metadata.functions[it.first.as<string>()].aob;
      auto trailingBytes = aob.find(config.trailingBytes);
      aob = aob.substr(0, trailingBytes);

      auto cursor = (byte*)addy;
      short b;
      for (int i = 0; i < aob.size(); i += 2) {
        while (isspace(aob[i])) {
          i++;
        }
        if (isxdigit(aob[i])) {
          sscanf(&aob[i], "%2hx", &b);
          if (b != *cursor) {
            allGood = false;
            break;
          }
        }
        cursor++;
      }

      if (!allGood) {
        break;
      }
    }

    return allGood;
  }
  void AddressFacade::search() {
    vector<string_view> patterns;
    for (const auto& it : metadata.basePointers) {
      keys.push_back(it.first);
      patterns.push_back(it.second.aob);
    }
    divider = keys.size();
    for (const auto& it : metadata.functions) {
      keys.push_back(it.first);
      patterns.push_back(it.second.aob);
    }

    auto scope = getScanRange(exeBase);

    findInMemory(
        patterns,
        scope.first,
        scope.second,
        [this](auto idx, auto address) { handleFoundAddress(idx, address); },
        config.trailingBytes);
  }
  bool AddressFacade::foundAllAddresses() {
    return addresses.basePointers.size() + addresses.functions.size() == keys.size();
  }
  const Addresses& AddressFacade::getNewAddreses() {
    return addresses;
  }
  string_view AddressFacade::getOutputName() {
    return config.addresses;
  }

  void AddressFacade::handleFoundAddress(unsigned int idx, Pointer address) {
    if (idx >= divider) {
      addresses.functions[keys[idx].data()] = address - exeBase;
    } else {
      auto offset = metadata.basePointers[keys[idx].data()].offset;
      auto constant = *(int*)(address + offset);
      auto basePtr = address + offset + 4 + constant;

      // clang-format off
      addresses.basePointers[keys[idx].data()] = {
        .address = basePtr - exeBase,
        .source = address - exeBase,
      };
      // clang-format on
    }
  }
}  // namespace plugin
