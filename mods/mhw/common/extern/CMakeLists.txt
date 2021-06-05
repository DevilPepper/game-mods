include(FetchContent)
include(cmake/add_FetchContent_MakeAvailableNotAll.cmake)

FetchContent_Declare(
        stuff
        GIT_REPOSITORY "https://github.com/Stuff-Mods/StuffLib"
        GIT_TAG "f29878acf1f057cdd387e3286a5b78b065cb6054"
)

FetchContent_MakeAvailableNotAll(stuff)
