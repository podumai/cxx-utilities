cmake_minimum_required(VERSION 3.30)

find_package(Git QUIET)
if(GIT_FOUND)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_TAG
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
    )

    if(GIT_TAG)
        set(PROJECT_VERSION ${GIT_TAG})
    endif()
endif()

if(NOT PROJECT_VERSION)
    set(PROJECT_VERSION "1.0.0")
endif()

project(
  CXXUtilities
  VERSION ${PROJECT_VERSION}
  LANGUAGES CXX
  DESCRIPTION "Laboratory work about useful C++ utilities")

set(CMAKE_CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CI_CD_RELEASE)
  set(BUILD_SHARED_LIBS OFF)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".lib")
  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang"
     OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"
     OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-mtune=generic -march=x86-64)
    add_link_options(-static)
  elseif(CMAKE_CXX_COMPILER_ID STREQ "MSVC")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultithreadedDebug")
  else()
    message(
      FATAL_ERROR
        "[${PROJECT_NAME}] Configuration for ${CMAKE_CXX_COMPILER_ID} missing.")
  endif()
endif()

if($ENV{DEV})
  find_program(CLANG_TIDY_EXE NAMES "clang-tidy" REQUIRED)
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
                           "--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy")
endif()

find_package(Catch2 3 REQUIRED)
include(CTest)
include(Catch)

add_subdirectory(app)
add_subdirectory(src)
add_subdirectory(tests)
