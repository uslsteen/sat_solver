# NOTE: Force it to prevent building failure
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_library(sat_runtime_lib STATIC sat.cppm)
target_sources(sat_runtime_lib
    PUBLIC FILE_SET
    CXX_MODULES
    FILES
    sat.cppm
)
#
add_executable(sat_runtime main.cc)
#
set_target_properties(sat_runtime PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_BINARY_DIR}/bin/")
#
target_link_libraries(sat_runtime sat_runtime_lib)