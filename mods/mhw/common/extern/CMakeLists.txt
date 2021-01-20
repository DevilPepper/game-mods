include(FetchContent)
include(cmake/add_FetchContent_MakeAvailableNotAll.cmake)
FetchContent_Declare(
        nlohmann-json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.9.1
)
FetchContent_Declare(
        stuff
        GIT_REPOSITORY "https://github.com/Stuff-Mods/StuffLib"
        GIT_TAG "251a38551b0705479e3ba4a6bd1afc0252a7899d"
)
FetchContent_Declare(
        loader
        GIT_REPOSITORY "https://github.com/ForksKnivesAndSpoons/MHW-QuestLoader"
        GIT_TAG "8f09e38c6fbad6fa05e6dce3d513cb48ce5fa0dd"
)

FetchContent_MakeAvailableNotAll(nlohmann-json)
FetchContent_MakeAvailableNotAll(stuff)
FetchContent_MakeAvailableNotAll(loader)
