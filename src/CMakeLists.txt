add_library(foo)

target_sources(foo
    PUBLIC
    FILE_SET CXX_MODULES FILES
    foo.cxx
)

add_executable(hello main.cxx)
#
set_target_properties(hello PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                        "${PROJECT_BINARY_DIR}/bin/")
#
target_link_libraries(hello foo)