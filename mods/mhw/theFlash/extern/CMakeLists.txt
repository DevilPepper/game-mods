include(FetchContent)
include(cmake/add_FetchContent_MakeAvailableNotAll.cmake)
FetchContent_Declare(
        nlohmann-json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.9.1
)
FetchContent_Declare(
        loader
        GIT_REPOSITORY "https://github.com/ForksKnivesAndSpoons/MHW-QuestLoader"
        GIT_TAG "8f09e38c6fbad6fa05e6dce3d513cb48ce5fa0dd"
)
FetchContent_Declare(
  StuffLib
  GIT_REPOSITORY "https://github.com/SupaStuff/MHW-GamepadPlugins.git"
  GIT_TAG "dda57779050766e205e36f02fa446dd2c97d3550"
)

FetchContent_MakeAvailableNotAll(nlohmann-json)
FetchContent_MakeAvailableNotAll(loader)
FetchContent_MakeAvailable(StuffLib)
