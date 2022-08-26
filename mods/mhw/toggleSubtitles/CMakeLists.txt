project(ToggleSubtitles)
FILE(GLOB_RECURSE ToggleSubtitlesSources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src *.h *.cpp)
add_library(ToggleSubtitles MODULE ${ToggleSubtitlesSources})
target_compile_features(ToggleSubtitles PRIVATE cxx_std_20)
target_link_libraries(ToggleSubtitles
PRIVATE
  stuff
  mhw-common
  GamepadLib
  yaml-cpp
)
