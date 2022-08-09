project(LockOn2MapPin)
FILE(GLOB_RECURSE LockOn2MapPinSources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR} *.h *.cpp)
add_library(LockOn2MapPin SHARED ${LockOn2MapPinSources})
target_compile_features(LockOn2MapPin PRIVATE cxx_std_20)
target_link_libraries(LockOn2MapPin
  PRIVATE
    stuff
    mhw-common
    yaml-cpp
)
