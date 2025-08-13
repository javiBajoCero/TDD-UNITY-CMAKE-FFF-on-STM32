cmake_minimum_required(VERSION 3.16)

# 1) Create the test exe FIRST — name must match what the subdir expects. Add Unity runner + unity.c; then add all CubeMX sources (except main.c).
set(TEST_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/Core/main.c
  ${CMAKE_CURRENT_LIST_DIR}/unity/src/unity.c
)

add_executable(UnitTests ${TEST_SOURCES})
project(UnitTests C ASM)

include(CTest)
enable_testing()

# 1) Bring in your existing CubeMX CMake project (read-only).
#    This is the CMake that already sets device macro, HAL/CMSIS includes,
#    startup, linker script, optimization flags, etc.
set(CUBEMX_DIR ${CMAKE_SOURCE_DIR}/../cmake/stm32cubemx)
add_subdirectory(${CUBEMX_DIR} ${CMAKE_BINARY_DIR}/stm32cubemx EXCLUDE_FROM_ALL)

# 2) Find the app executable target from that subdir.
#    You can skip auto-detect and pass -DAPP_TARGET=<name> to cmake if you want.
if(NOT DEFINED APP_TARGET)
  get_property(_allTargets GLOBAL PROPERTY TARGETS)
  foreach(t ${_allTargets})
    get_target_property(_type ${t} TYPE)
    if(NOT _type STREQUAL "EXECUTABLE")
      continue()
    endif()
    # Heuristic: the CubeMX app usually has a Core/Src/main.c
    get_target_property(_srcs ${t} SOURCES)
    foreach(s ${_srcs})
      if(s MATCHES ".*/Core/Src/main\\.c$")
        set(APP_TARGET ${t})
        break()
      endif()
    endforeach()
    if(APP_TARGET)
      break()
    endif()
  endforeach()
  if(NOT APP_TARGET)
    message(FATAL_ERROR "Could not auto-detect CubeMX app target. Pass -DAPP_TARGET=<name> to cmake.")
  endif()
endif()
message(STATUS "Using CubeMX app target: ${APP_TARGET}")

# 3) Mirror the app target's configuration.
get_target_property(APP_SRCS  ${APP_TARGET} SOURCES)
get_target_property(APP_INCS  ${APP_TARGET} INCLUDE_DIRECTORIES)
get_target_property(APP_DEFS  ${APP_TARGET} COMPILE_DEFINITIONS)
get_target_property(APP_COPTS ${APP_TARGET} COMPILE_OPTIONS)
get_target_property(APP_LOPTS ${APP_TARGET} LINK_OPTIONS)
get_target_property(APP_LIBS  ${APP_TARGET} LINK_LIBRARIES)

# Remove the app's main.c; our Unity main will be the entry.
set(FILTERED_APP_SRCS "")
foreach(s ${APP_SRCS})
  get_filename_component(n ${s} NAME)
  if(n MATCHES "^main\\.c$")
    continue()
  endif()
  list(APPEND FILTERED_APP_SRCS ${s})
endforeach()

target_sources(UnitTestsPRIVATE ${FILTERED_APP_SRCS})

# Unity config (optional): put unity_config.h in tests/Core and enable this.
target_compile_definitions(UnitTests PRIVATE UNITY_INCLUDE_CONFIG_H)
target_include_directories(UnitTests PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/unity/src
  ${CMAKE_CURRENT_LIST_DIR}/fff
  ${CMAKE_CURRENT_LIST_DIR}/Core
)

# Inherit everything from the app target (device macro, includes, flags, ld, libs).
if(APP_INCS)
  target_include_directories(UnitTests PRIVATE ${APP_INCS})
endif()

if(APP_DEFS)
  target_compile_definitions(UnitTests PRIVATE ${APP_DEFS})
endif()

if(APP_COPTS)
  target_compile_options(UnitTests PRIVATE ${APP_COPTS})
endif()

if(APP_LOPTS)
  target_link_options(UnitTests PRIVATE ${APP_LOPTS})
endif()

if(APP_LIBS)
  target_link_libraries(UnitTests PRIVATE ${APP_LIBS})
endif()


target_compile_features(UnitTests PRIVATE c_std_99)
