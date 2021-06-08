include(FetchContent)
include(cmake/add_FetchContent_MakeAvailableNotAll.cmake)

FetchContent_Declare(
        GamepadLib
        GIT_REPOSITORY "https://github.com/Stuff-Mods/GamepadLib"
        GIT_TAG "34e6d6cdfc0a3d654cf2360583c06bd5a66616fc"
)
FetchContent_Declare(
        stuff
        GIT_REPOSITORY "https://github.com/Stuff-Mods/StuffLib"
        GIT_TAG "ebe57dbca3e93ea732dacf9f2f590c868682ce80"
)
FetchContent_Declare(
        mhw-common
        GIT_REPOSITORY "https://github.com/Stuff-Mods/MHW-CommonLib"
        GIT_TAG "11d285239eb0e7de96481919d25f5b6771cf1013"
)

FetchContent_MakeAvailable(GamepadLib)
FetchContent_MakeAvailable(stuff)
FetchContent_MakeAvailable(mhw-common)
