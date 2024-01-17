add_library(sat_compiletime_lib STATIC sat.cppm)
target_sources(sat_compiletime_lib
    PUBLIC FILE_SET
    CXX_MODULES
    FILES
    sat.cppm
)

add_executable(sat_compiletime main.cc)

#
set_target_properties(sat_compiletime PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_BINARY_DIR}/bin/")
#
target_link_libraries(sat_compiletime sat_compiletime_lib)