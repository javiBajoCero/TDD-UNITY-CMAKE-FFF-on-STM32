cmake_minimum_required(VERSION 3.16)
project(UnitTests C)

include(CTest)
enable_testing()

set(TEST_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/test_ledDriver.c
    ${CMAKE_CURRENT_LIST_DIR}/test_sanity.c

    ${CMAKE_CURRENT_LIST_DIR}/unity/src/unity.c
)

add_executable(unit_tests ${TEST_SOURCES})

file(GLOB_RECURSE DRIVER_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/../Driver/*
)

target_include_directories(unit_tests PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/unity/src
    ${CMAKE_CURRENT_LIST_DIR}/fff

    ${CMAKE_CURRENT_LIST_DIR}/../UserCore
    ${CMAKE_CURRENT_LIST_DIR}/../Core/Inc
    ${CMAKE_CURRENT_LIST_DIR}/../Core/src

    ${DRIVER_INCLUDE_DIRS}
)

target_compile_features(unit_tests PRIVATE c_std_99)

add_test(NAME unit_tests COMMAND unit_tests)
