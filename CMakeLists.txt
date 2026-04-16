cmake_minimum_required(VERSION 3.25)

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "macOS architecture")

include(FetchContent)

message(STATUS "Fetching max-sdk-base")
FetchContent_Declare(
  max-sdk-base
  GIT_REPOSITORY https://github.com/Cycling74/max-sdk-base.git
  GIT_TAG cmake-improvements
)
FetchContent_MakeAvailable(max-sdk-base)

project(MaxSDK)

add_subdirectory(source/advanced)
add_subdirectory(source/audio)
add_subdirectory(source/basics)
add_subdirectory(source/dictionary)
add_subdirectory(source/gl)
add_subdirectory(source/matrix)
add_subdirectory(source/mc)
add_subdirectory(source/misc)
add_subdirectory(source/patcher)
add_subdirectory(source/ui)

