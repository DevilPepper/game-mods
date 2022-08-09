include(FetchContent)
include(cmake/add_FetchContent_MakeAvailableNotAll.cmake)

FetchContent_Declare(
        stuff
        GIT_REPOSITORY "https://github.com/Stuff-Mods/StuffLib"
        GIT_TAG "ebe57dbca3e93ea732dacf9f2f590c868682ce80"
)

FetchContent_MakeAvailableNotAll(stuff)
