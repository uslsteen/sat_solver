add_library(sat_runtime_lib STATIC sat.cppm)
target_sources(sat_runtime_lib
    PUBLIC FILE_SET
    CXX_MODULES
    FILES
    sat.cppm
)

add_executable(sat_solver main.cc)
#
set_target_properties(sat_solver PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_BINARY_DIR}/bin/")
#
target_link_libraries(sat_solver sat_runtime_lib)