add_library(Lab2Utility)
add_library(Lab2Utility::Lab2Utility ALIAS Lab2Utility)
target_sources(
  Lab2Utility
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_SOURCE_DIR}/include"
  FILES "${CMAKE_SOURCE_DIR}/include/tpu/utility.hpp"
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/utility.cpp"
)
