include(FetchContent)
include(cmake/add_FetchContent_MakeAvailableNotAll.cmake)

FetchContent_Declare(
  stuff
  GIT_REPOSITORY "https://github.com/Stuff-Mods/StuffLib"
  GIT_TAG "c7f456d473d9168c66ed5a3dd7d4bf3ea9cfcbc8"
)

FetchContent_MakeAvailable(stuff)
