cmake_minimum_required(VERSION 3.16)
project(UnitTests C ASM)

include(CTest)
enable_testing()

# 1) Create the executable target *first*. Name must match ${CMAKE_PROJECT_NAME}.
#    Leave it empty so the CubeMX subdir can add its sources.
add_executable(${CMAKE_PROJECT_NAME} "")

# 2) Bring in the CubeMX cmake which will add HAL/CMSIS sources and link flags to our target.
set(CUBEMX_DIR ${CMAKE_SOURCE_DIR}/../cmake/stm32cubemx)
add_subdirectory(${CUBEMX_DIR} ${CMAKE_BINARY_DIR}/stm32cubemx EXCLUDE_FROM_ALL)

# 3) Remove CubeMX's app main.c from the target (we will use Unity's main instead).
get_target_property(_app_srcs ${CMAKE_PROJECT_NAME} SOURCES)
set(_filtered_srcs ${_app_srcs})
foreach(s IN LISTS _app_srcs)
  if(s MATCHES "/Core/Src/main\\.c$")
    list(REMOVE_ITEM _filtered_srcs "${s}")
  endif()
endforeach()
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY SOURCES "${_filtered_srcs}")

# 4) Add Unity runner and unity.c
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/Core/main.c          # your Unity test runner main
  ${CMAKE_CURRENT_LIST_DIR}/unity/src/unity.c
  ${CMAKE_CURRENT_LIST_DIR}/Core/test_wolksvagen.c
)

# Remove any -T that points to tests/
string(REGEX REPLACE " *-T\"?[^\"]+\"?" "" CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

# Add the correct absolute path (tests/.. is repo root)
set(_ld "${CMAKE_CURRENT_SOURCE_DIR}/../STM32U083xx_FLASH.ld")
target_link_options(UnitTests PRIVATE "-T${_ld}")


# 5) Test-specific includes/defs
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/unity/src
  ${CMAKE_CURRENT_LIST_DIR}/fff
  ${CMAKE_CURRENT_LIST_DIR}/Core
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../UserCore
)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE UNITY_INCLUDE_CONFIG_H)

# Usual C standard
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE c_std_99)

# Register the test exe (it will be the same ${CMAKE_PROJECT_NAME})
add_test(NAME unit_tests COMMAND ${CMAKE_PROJECT_NAME})
