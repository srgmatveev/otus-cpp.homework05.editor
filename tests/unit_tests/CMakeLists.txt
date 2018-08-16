FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(GTest REQUIRED)

set(GMOCK_BOTH_LIBRARIES gmock gmock_main)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Unit_Tests_run
         Shapes_test.cpp)
target_link_libraries(Unit_Tests_run ${GTEST_BOTH_LIBRARIES})
target_link_libraries(Unit_Tests_run ${GMOCK_BOTH_LIBRARIES})
target_link_libraries(Unit_Tests_run ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(Unit_Tests_run PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )
