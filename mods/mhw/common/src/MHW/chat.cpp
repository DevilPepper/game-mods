#include "chat.h"

#include <format>

namespace MHW {
  Chat::Chat(Pointer instance, SendSystemMessage systemMessage) :
      instance(instance),
      systemMessage(systemMessage) {}

  void Chat::sendSystemMessage(const std::string msg, bool isPurple) {
    systemMessage(*(undefined **)instance, (undefined *)msg.c_str(), -1, -1, isPurple);
  }

  // TODO: Implement a lookup for both of these
  std::string Chat::wrapIcon(Icon icon) {
    return std::format("<ICON {}>", "INFINITY");
  }
  std::string Chat::wrapColor(std::string msg, Color color) {
    return std::format("<STYL {}>{}</STYL>", "MOJI_LIGHTGREEN_DEFAULT", msg);
  }
}  // namespace MHW
