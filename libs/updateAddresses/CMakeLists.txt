project(UpdateAddresses)
FILE(GLOB_RECURSE UpdateAddressesSources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src *.h *.cpp)
add_library(UpdateAddresses MODULE ${UpdateAddressesSources})
target_compile_features(UpdateAddresses PRIVATE cxx_std_20)
target_link_libraries(UpdateAddresses
  PRIVATE
    stuff
    yaml-cpp
)
