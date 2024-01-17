add_library(sat_hybrid_lib STATIC sat.cppm)
target_sources(sat_hybrid_lib
    PUBLIC FILE_SET
    CXX_MODULES
    FILES
    sat.cppm
)

#
add_executable(sat_hybrid main.cc)

#
set_target_properties(sat_hybrid PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_BINARY_DIR}/bin/")
#
target_link_libraries(sat_hybrid sat_hybrid_lib)