cmake_minimum_required(VERSION 3.30)
project(
  CXXUtilities
  VERSION 1.0.0
  LANGUAGES CXX
  DESCRIPTION "Laboratory work about useful C++ utilities"
)

set(CMAKE_CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if($ENV{DEV})
  find_program(CLANG_TIDY_EXE NAMES "clang-tidy" REQUIRED)
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy")
endif()

find_package(Catch2 3 REQUIRED)
include(CTest)
include(Catch)

add_subdirectory(app)
add_subdirectory(src)
add_subdirectory(tests)
