#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <optional>
#include <string_view>
#include <tpu/utility.hpp>

namespace lab::test {

TEST_CASE("ParseRow function test[1]") {
  constexpr std::string_view kQueryInput{"127.0.0.1\t1\t2\n"};
  constexpr std::array<std::string_view, 3> kExpectedResult{"127.0.0.1", "1", "2"};
  const auto result{lab::utility::ParseRow(kQueryInput)};
  REQUIRE(std::ranges::equal(*result, kExpectedResult));
}

TEST_CASE("ParseRow function test[2]") {
  constexpr std::string_view kQueryInput{""};
  constexpr auto kExpectedOutput{std::nullopt};
  const auto result{lab::utility::ParseRow(kQueryInput)};
  REQUIRE(kExpectedOutput == result);
}

TEST_CASE("ParseRow function test[3]") {
  constexpr std::string_view kQueryInput;
  constexpr auto kExpectedOutput{std::nullopt};
  const auto result{lab::utility::ParseRow(kQueryInput)};
  REQUIRE(kExpectedOutput == result);
}

TEST_CASE("ParseIp function test") {
  constexpr std::string_view kQueryInput{"127.0.0.1"};
  constexpr lab::ParsedIpType kExpectedResult{lab::ParsedIpType{127, 0, 0, 1}};
  const auto result{lab::utility::ParseIp(kQueryInput)};
  REQUIRE((result == kExpectedResult));
}

}  // namespace lab::test
