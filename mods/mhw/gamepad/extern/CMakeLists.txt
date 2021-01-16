include(FetchContent)
include(cmake/add_FetchContent_MakeAvailableNotAll.cmake)

FetchContent_Declare(
        minhook
        GIT_REPOSITORY "https://github.com/TsudaKageyu/minhook"
        GIT_TAG "3f2e34976c1685ee372a09f54c0c8c8f4240ef90"
)
FetchContent_Declare(
        GamepadLib
        GIT_REPOSITORY "https://github.com/Stuff-Mods/GamepadLib"
        GIT_TAG "644b76aa89cea7c12c6a7d5a2641ecb67e44b29a"
)
FetchContent_Declare(
        stuff
        GIT_REPOSITORY "https://github.com/Stuff-Mods/StuffLib"
        GIT_TAG "9b0108612a592e77e42cf9bced08af9bce532b69"
)
FetchContent_Declare(
        mhw-common
        GIT_REPOSITORY "https://github.com/Stuff-Mods/MHW-CommonLib"
        GIT_TAG "38bdbc1b2e21112c45443de5667dc01285825c61"
)

FetchContent_MakeAvailableNotAll(minhook)
FetchContent_MakeAvailable(GamepadLib)
FetchContent_MakeAvailable(stuff)
FetchContent_MakeAvailable(mhw-common)
