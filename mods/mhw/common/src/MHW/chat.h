#pragma once

#include <types/address.h>
#include <types/ghidra.h>

#include <string>

#include "chatMarkup.h"

namespace MHW {
  using stuff::types::Pointer;
  using namespace ghidra::types;
  using SendSystemMessage = void (*)(undefined *, undefined *, float, uint, undefined1);

  class Chat {
   public:
    Chat(Pointer instance, SendSystemMessage systemMessage);
    void sendSystemMessage(std::string msg, bool isPurple);
    std::string wrapIcon(Icon icon);
    std::string wrapColor(std::string msg, Color color);

   private:
    Pointer instance;
    SendSystemMessage systemMessage;
  };
}  // namespace MHW
