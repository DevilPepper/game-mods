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
        GIT_TAG "2ac3bfda4c075fc8a6bdc25a94bf7d750c6f95de"
)

FetchContent_MakeAvailableNotAll(nlohmann-json)
FetchContent_MakeAvailableNotAll(stuff)
