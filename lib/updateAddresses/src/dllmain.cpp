// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <yaml-cpp/yaml.h>

#include <format>
#include <fstream>
#include <iostream>

#include "converters/AddressesConverter.h"
#include "plugin/AddressFacade.h"

using plugin::AddressFacade;
using std::cout;

AddressFacade facade;

void sanityCheck() {
  if (!facade.isGood()) {
    facade.search();

    if (!facade.foundAllAddresses()) {
      cout << "Didn't find all addresses... You might want to report some broken plugin(s)\n";
    }

    YAML::Emitter yaml;
    std::ofstream file(facade.getOutputName().data(), std::ios::binary);

    yaml << YAML::Hex << facade.getNewAddreses();
    file << yaml.c_str() << std::endl;
    file.flush();
    file.close();

    cout << std::format(
        "{} was updated. You don't have to do anything,\n"
        "\tbut you can send the updated file to the maintainers if you like.\n",
        facade.getOutputName());
  } else {
    cout << "All good!\n";
  }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
      sanityCheck();
      break;
    }
    case DLL_PROCESS_DETACH: {
      break;
    }
    default:
      break;
  }
  return TRUE;
}
