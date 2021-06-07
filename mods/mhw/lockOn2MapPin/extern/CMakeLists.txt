include(FetchContent)
include(cmake/add_FetchContent_MakeAvailableNotAll.cmake)
FetchContent_Declare(
  loader
  GIT_REPOSITORY "https://github.com/ForksKnivesAndSpoons/MHW-QuestLoader"
  GIT_TAG "8f09e38c6fbad6fa05e6dce3d513cb48ce5fa0dd"
)
FetchContent_Declare(
  GamepadLib
  GIT_REPOSITORY "https://github.com/Stuff-Mods/GamepadLib"
  GIT_TAG "644b76aa89cea7c12c6a7d5a2641ecb67e44b29a"
)
FetchContent_Declare(
  stuff
  GIT_REPOSITORY "https://github.com/Stuff-Mods/StuffLib"
  GIT_TAG "ebe57dbca3e93ea732dacf9f2f590c868682ce80"
)
FetchContent_Declare(
  mhw-common
  GIT_REPOSITORY "https://github.com/Stuff-Mods/MHW-CommonLib"
  GIT_TAG "395965381400d02fd49aa9a67946a18b8935e414"
)

FetchContent_MakeAvailableNotAll(loader)
FetchContent_MakeAvailable(GamepadLib)
FetchContent_MakeAvailable(stuff)
FetchContent_MakeAvailable(mhw-common)
