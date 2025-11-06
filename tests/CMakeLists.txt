add_executable(Lab2Tests)
target_sources(
  Lab2Tests
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/test.cpp"
)
target_compile_features(
  Lab2Tests
  PRIVATE
  cxx_std_23
)
set_target_properties(
  Lab2Tests
  PROPERTIES
  OUTPUT_NAME "ip-filter-test"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
target_link_libraries(
  Lab2Tests
  PRIVATE
  Catch2::Catch2
  Catch2::Catch2WithMain
  Lab2Utility::Lab2Utility
)

catch_discover_tests(Lab2Tests)
