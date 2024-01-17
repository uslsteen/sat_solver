cmake_minimum_required(VERSION 3.28)

if("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    message(
        FATAL_ERROR
        "In-source builds are disabled.
  Please create a subfolder and use `cmake ..` inside it.
  NOTE: cmake will now create CMakeCache.txt and CMakeFiles/*.
  You must delete them, or cmake will refuse to work.")
endif()

project(module_example CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)

option(BUILD_TESTS "Build tests" OFF)
option(ENABLE_WERROR "Enable -Werror option (CI)" OFF)

if(BUILD_TESTS)
    enable_testing()
endif()

add_subdirectory(src)
add_subdirectory(tests)
