#pragma once

#include <MHW/addy.h>
#include <MHW/chat.h>
#include <types/address.h>

namespace model {
  using MHW::SendSystemMessage;
  using stuff::types::Pointer;

  class Addresses : public MHW::Addy {
   public:
    Pointer chat_instance;

    SendSystemMessage fnSendSystemMessage;
  };
}  // namespace model
