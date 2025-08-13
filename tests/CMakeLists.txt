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

# 2) Find the app executable target from the CubeMX subdir.
if(NOT DEFINED APP_TARGET)
  # Prefer a target that has Core/Src/main.c or Core/src/main.c
  set(_found "")
  get_property(_allTargets GLOBAL PROPERTY TARGETS)
  foreach(t ${_allTargets})
    get_target_property(_type ${t} TYPE)
    if(NOT _type STREQUAL "EXECUTABLE")
      continue()
    endif()
    get_target_property(_srcs ${t} SOURCES)
    foreach(s ${_srcs})
      if(s MATCHES ".*/Core/[Ss]rc/main\\.c$")
        set(_found ${t})
        break()
      endif()
    endforeach()
    if(_found)
      break()
    endif()
  endforeach()

  # If not found by heuristic, see what executables were added by the CubeMX dir
  if(NOT _found)
    # Collect exe targets defined in the CubeMX source dir
    get_directory_property(_cubeTargets DIRECTORY ${CUBEMX_DIR} BUILDSYSTEM_TARGETS)
    set(_cubeExes "")
    foreach(t ${_cubeTargets})
      get_target_property(_type ${t} TYPE)
      if(_type STREQUAL "EXECUTABLE")
        list(APPEND _cubeExes ${t})
      endif()
    endforeach()
    list(LENGTH _cubeExes _nexes)
    if(_nexes EQUAL 1)
      list(GET _cubeExes 0 _found)
    endif()
  endif()

  if(_found)
    set(APP_TARGET ${_found})
  else()
    # Last resort: show what we saw and fail with a clear hint
    message(STATUS "Could not auto-detect the CubeMX app target.")
    message(STATUS "Hint: pass -DAPP_TARGET=<name>. Executable targets seen:")
    foreach(t ${_allTargets})
      get_target_property(_type ${t} TYPE)
      if(_type STREQUAL "EXECUTABLE")
        message(STATUS "  - ${t}")
      endif()
    endforeach()
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
