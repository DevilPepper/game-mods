project(ReturnTimer)
FILE(GLOB_RECURSE ReturnTimerSources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src *.h *.cpp)
add_library(ReturnTimer SHARED ${ReturnTimerSources})
target_compile_features(ReturnTimer PRIVATE cxx_std_20)
target_link_libraries(ReturnTimer
  PRIVATE
    stuff
    mhw-common
    GamepadLib
    yaml-cpp
)
