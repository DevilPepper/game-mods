project(mhw-common)
FILE(GLOB_RECURSE mhwSources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src *.h *.cpp)
add_library(mhw-common STATIC ${mhwSources})
target_include_directories(mhw-common PUBLIC src)
target_compile_features(mhw-common PRIVATE cxx_std_20)
target_link_libraries(mhw-common PUBLIC stuff)
