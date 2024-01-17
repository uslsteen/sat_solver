set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TESTLIST sat_runtime sat_compiletime)

if(BUILD_TESTS)
    find_package(GTest REQUIRED)
    include(GoogleTest)

    foreach(TARGET ${TESTLIST})
        add_executable(${TARGET}_test ${TARGET}.cc)

        target_link_libraries(${TARGET}_test PRIVATE ${TARGET}_lib)
        target_link_libraries(${TARGET}_test PRIVATE gtest_main
            gtest
        )

        gtest_discover_tests(
            ${TARGET}_test
            EXTRA_ARGS --gtest_color=yes
            PROPERTIES LABELS unit
        )
    endforeach()
endif()
