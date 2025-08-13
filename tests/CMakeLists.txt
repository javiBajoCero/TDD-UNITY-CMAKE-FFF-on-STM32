cmake_minimum_required(VERSION 3.16)

set(MX_Defines_Syms 
	USE_NUCLEO_64 
	USE_HAL_DRIVER 
	STM32U083xx
    $<$<CONFIG:Debug>:DEBUG>
)

# Startup + linker (match your CubeMX output names/paths)
set(STARTUP_ASM ${CMAKE_CURRENT_LIST_DIR}/../startup_stm32u083xx.s)
set(LD_SCRIPT   ${CMAKE_CURRENT_LIST_DIR}/../STM32U083xx_FLASH.ld)

project(UnitTests C)

include(CTest)
enable_testing()

set(TEST_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/Core/main.c

    ${CMAKE_CURRENT_LIST_DIR}/unity/src/unity.c
)

add_executable(unit_tests ${TEST_SOURCES})

target_include_directories(unit_tests PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/unity/src
    ${CMAKE_CURRENT_LIST_DIR}/fff

    ${CMAKE_CURRENT_LIST_DIR}/../UserCore
    ${CMAKE_CURRENT_LIST_DIR}/../Core/Inc
    ${CMAKE_CURRENT_LIST_DIR}/../Core/src

    ${CMAKE_CURRENT_LIST_DIR}/../Drivers/STM32U0xx_HAL_Driver/Src
    ${CMAKE_CURRENT_LIST_DIR}/../Drivers/STM32U0xx_HAL_Driver/Inc
    ${CMAKE_CURRENT_LIST_DIR}/../Drivers/BSP/STM32U0xx_Nucleo
)

target_compile_features(unit_tests PRIVATE c_std_99)

add_test(NAME unit_tests COMMAND unit_tests)
