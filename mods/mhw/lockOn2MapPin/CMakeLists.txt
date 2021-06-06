# Need to set these env vars CC=CL CXX=CL | CC=CL.exe && CXX=CL.exe
cmake_minimum_required(VERSION 3.19)

if(DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
  set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "")
endif()

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(MHW-LockOn2MapPin CXX)

# Only do these if this is the main project, and not if it is included through
# add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  set(CMAKE_CXX_STANDARD 14)
  set(CXX_STANDARD_REQUIRED ON)
  add_compile_definitions(_MBCS)
  # set_property(GLOBAL)

  # Optionally set things like CMAKE_CXX_STANDARD,
  # CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDE's
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app. Note this needs to be done
  # in the main CMakeLists since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)

  # Docs only available if this is the main app
  # find_package(Doxygen)
  # if(Doxygen_FOUND)
  #   add_subdirectory(docs)
  # else()
  #   message(STATUS "Doxygen not found, not building docs")
  # endif()
endif()

find_package(yaml-cpp REQUIRED)

add_subdirectory(extern)
add_subdirectory(src)
