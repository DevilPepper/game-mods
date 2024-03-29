#pragma once

#include <string>

// Copied from here: https://gist.github.com/Haato3o/54c64b3928aac31de890061b475bd4af
namespace MHW {
  enum Color {
    MOJI_WHITE_DEFAULT,
    MOJI_WHITE_SELECTED,
    MOJI_WHITE_SELECTED2,
    MOJI_WHITE_DISABLE,
    MOJI_WHITE_DEFAULT2,
    MOJI_BLACK_DEFAULT,
    MOJI_RED_DEFAULT,
    MOJI_RED_SELECTED,
    MOJI_RED_SELECTED2,
    MOJI_RED_DISABLE,
    MOJI_YELLOW_DEFAULT,
    MOJI_YELLOW_SELECTED,
    MOJI_YELLOW_SELECTED2,
    MOJI_YELLOW_DISABLE,
    MOJI_ORANGE_DEFAULT,
    MOJI_ORANGE_SELECTED,
    MOJI_ORANGE_SELECTED2,
    MOJI_ORANGE_DISABLE,
    MOJI_GREEN_DEFAULT,
    MOJI_GREEN_SELECTED,
    MOJI_GREEN_SELECTED2,
    MOJI_GREEN_DISABLE,
    MOJI_SLGREEN_DEFAULT,
    MOJI_SLGREEN_SELECTED,
    MOJI_SLGREEN_SELECTED2,
    MOJI_SLGREEN_DISABLE,
    MOJI_SLGREEN2_DEFAULT,
    MOJI_SLGREEN2_SELECTED,
    MOJI_SLGREEN2_SELECTED2,
    MOJI_SLGREEN2_DISABLE,
    MOJI_LIGHTBLUE_DEFAULT,
    MOJI_LIGHTBLUE_SELECTED2,
    MOJI_LIGHTBLUE_SELECTED,
    MOJI_LIGHTBLUE_DISABLE,
    MOJI_LIGHTBLUE2_DEFAULT,
    MOJI_LIGHTBLUE2_SELECTED2,
    MOJI_LIGHTBLUE2_SELECTED,
    MOJI_LIGHTBLUE2_DISABLE,
    MOJI_LIGHTGREEN_DEFAULT,
    MOJI_LIGHTGREEN_SELECTED,
    MOJI_LIGHTGREEN_SELECTED2,
    MOJI_LIGHTGREEN_DISABLE,
    MOJI_LIGHTYELLOW_DEFAULT,
    MOJI_LIGHTYELLOW_SELECTED,
    MOJI_LIGHTYELLOW_SELECTED2,
    MOJI_LIGHTYELLOW_DISABLE,
    MOJI_LIGHTYELLOW2_DEFAULT,
    MOJI_LIGHTYELLOW2_SELECTED,
    MOJI_LIGHTYELLOW2_SELECTED2,
    MOJI_LIGHTYELLOW2_DISABLE,
    MOJI_BROWN_DEFAULT,
    MOJI_BROWN_SELECTED2,
    MOJI_BROWN_SELECTED,
    MOJI_BROWN_DISABLE,
    MOJI_YELLOW2_DEFAULT,
    MOJI_YELLOW2_SELECTED,
    MOJI_YELLOW2_SELECTED2,
    MOJI_YELLOW2_DISABLE,
    MOJI_ORENGE2_DEFAULT,
    MOJI_ORENGE2_SELECTED,
    MOJI_ORENGE2_SELECTED2,
    MOJI_ORENGE2_DISABLE,
    MOJI_PURPLE_DEFAULT,
    MOJI_PURPLE_SELECTED,
    MOJI_PURPLE_SELECTED2,
    MOJI_PURPLE_DISABLE,
    MOJI_RED2_DEFAULT,
    MOJI_RED2_SELECTED,
    MOJI_RED2_SELECTED2,
    MOJI_RED2_DISABLE,
    MOJI_BLUE_DEFAULT,
    MOJI_BLUE_SELECTED,
    MOJI_BLUE_SELECTED2,
    MOJI_BLUE_DISABLE,
    MOJI_PALEBLUE_DEFAULT,
    MOJI_PALEBLUE_SELECTED,
    MOJI_PALEBLUE_SELECTED2,
    MOJI_PALEBLUE_DISABLE,
  };

  enum Icon {
    DECIDE,
    CANCEL,
    PAD_RR,
    PAD_RD,
    PAD_RU,
    PAD_RL,
    PAD_KEY,
    PAD_KEY_V,
    PAD_KEY_H,
    PAD_LSTICK,
    PAD_RSTICK,
    PAD_L3,
    PAD_R3,
    PAD_L1,
    PAD_R1,
    PAD_L2,
    PAD_R2,
    OPTION,
    PAD_TOUCH,
    PAD_KEY_U,
    PAD_KEY_D,
    PAD_KEY_L,
    PAD_KEY_R,
    PL_L1,
    PL_L2,
    PL_R1,
    PL_R2,
    PAD_RELEASE,
    PAD_LSTICK_R,
    PAD_LSTICK_U,
    PAD_LSTICK_L,
    PAD_LSTICK_D,
    PAD_RSTICK_R,
    PAD_RSTICK_U,
    PAD_RSTICK_L,
    PAD_RSTICK_D,
    STAR_1,
    STAR_2,
    // INFINITY clashes with the constant INFINITY... The string is "INFINITY"
    INFINITY_SYMBOL,
    ALPHA,
    BETA,
    GAMMA,
    MALE,
    FEMALE,
    NOTE,
    TM,
    RTM,
    SLG_NEWS,
    TREASURE,
    STEAM_1,
    STEAM_2,
    STEAM_3,
  };
}  // namespace MHW
