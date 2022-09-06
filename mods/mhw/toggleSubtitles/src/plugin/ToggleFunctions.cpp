
#include <MHW/memory.h>

#include "ToggleSubtitles.h"

namespace plugin {

  using MHW::readMem;
  using MHW::writeMem;

  void ToggleSubtitles::toggleSubtitles() {
    bool subs_setting;
    bool subs_show;
    readMem(addresses.save_data, subtitle_setting, subs_setting);
    readMem(addresses.display_options, subtitle_show, subs_show);

    subs_setting ^= true;
    subs_show ^= true;
    writeMem(addresses.save_data, subtitle_setting, subs_setting);
    writeMem(addresses.display_options, subtitle_show, subs_show);
  }
}  // namespace plugin
