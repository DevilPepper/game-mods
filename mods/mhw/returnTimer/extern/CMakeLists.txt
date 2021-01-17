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
        GIT_TAG "4a1740e4bd291ade2c044a26bc39891226d0e17f"
)
FetchContent_Declare(
        stuff
        GIT_REPOSITORY "https://github.com/Stuff-Mods/StuffLib"
        GIT_TAG "9b0108612a592e77e42cf9bced08af9bce532b69"
)
FetchContent_Declare(
        mhw-common
        GIT_REPOSITORY "https://github.com/Stuff-Mods/MHW-CommonLib"
        GIT_TAG "d04f9465d46e7f09ef04766fa8ee165ad981d03a"
)

FetchContent_MakeAvailableNotAll(loader)
FetchContent_MakeAvailable(GamepadLib)
FetchContent_MakeAvailable(stuff)
FetchContent_MakeAvailable(mhw-common)
