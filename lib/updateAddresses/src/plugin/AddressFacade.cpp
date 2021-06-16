#include "AddressFacade.h"

#include <aob/PatternSearch.h>
#include <types/ghidra.h>
#include <yaml-cpp/yaml.h>

#include <format>
#include <functional>
#include <iostream>

#include "../converters/MetadataConverter.h"
#include "../converters/UpdateAddressesConverter.h"

namespace plugin {
  using ghidra::types::byte;
  using std::cout;
  using stuff::aob::PatternSearch::findInMemory;

  AddressFacade::AddressFacade() {
    exeBase = (Pointer)GetModuleHandle(NULL);
    config = YAML::LoadFile("UpdateAddresses.yaml").as<UpdateAddresses>();
    metadata = YAML::LoadFile(config.metadata).as<Metadata>();
  }
  bool AddressFacade::isGood() {
    // TODO: implement
    return false;
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

    cout << "Dictionary size: " << keys.size() << std::endl;
    cout << "Search space size: 0x2000000\n";

    findInMemory(
        patterns,
        (byte*)exeBase,
        (byte*)(exeBase + 0x2000000),
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
      cout << std::format("Found {} @ {:#0x}\n", keys[idx], address);
    } else {
      auto offset = metadata.basePointers[keys[idx].data()].offset;
      auto constant = *(int*)(address + offset);
      auto basePtr = address + offset + 4 + constant - exeBase;
      cout << std::format("Found AOB for {} @ {:#0x}\n", keys[idx], address);
      cout << std::format("\tBase Pointer is {:#0x}\n", basePtr);
    }
  }
}  // namespace plugin
