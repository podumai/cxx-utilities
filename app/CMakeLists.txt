add_executable(App)
target_sources(
  App
  PRIVATE
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_SOURCE_DIR}/include"
  FILES "${CMAKE_SOURCE_DIR}/include/tpu/utility.hpp"
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)
target_link_libraries(
  App
  PRIVATE
  Lab2Utility::Lab2Utility
)
set_target_properties(
  App
  PROPERTIES
  OUTPUT_NAME "ip-filter"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
