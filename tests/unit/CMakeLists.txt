# NOTE: Force it to prevent building failure
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

# Naive & lazy way to collect list of test targets
set(TESTLIST sat_runtime 
             sat_compile_time
             sat_hybrid)

if(BUILD_TESTS)
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
