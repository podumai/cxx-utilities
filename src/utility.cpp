/// @file src/utility.cpp

#include <algorithm>
#include <cstdio>
#include <format>
#include <functional>
#include <print>
#include <ranges>
#include <tpu/utility.hpp>
#include <utility>

/// @namespace lab::utility
/// @brief Namespace containing utility function for laboratory work
namespace lab::utility {

/// @brief Enumeration represents the byte indexes in ip address parsed as tuple.
/// @enum BytePosition
enum BytePosition : unsigned char { kUnknown = 0, kFirst = 0, kSecond = 1, kThird = 2, kFourth = 3 };

/// @brief Parses row as columns separeted by tab.
/// @param[in] row String representation of row following tsv format.
/// @return Parsed row in contigious container if row is valid, nullopt otherwise.
/// @throws std::bad_alloc (if allocation fails).
[[nodiscard]] auto ParseRow(std::string_view row) -> std::optional<std::vector<std::string_view>> {
  if (row.empty()) [[unlikely]] {
    return std::nullopt;
  }

  using SizeType = typename std::string_view::size_type;

  auto result = std::vector<std::string_view>{};
  auto current_index = SizeType{};
  while (current_index != std::string_view::npos) {
    const auto end = row.find('\t', current_index);
    const auto field = row.substr(current_index, end - current_index);
    result.push_back(field);
    current_index = end != std::string_view::npos ? end + 1 : end;
  }

  result.back().remove_suffix(1);

  return result;
}

/// @brief Function for parsing ip address and packing it in std::tuple.
/// @param[in] ip_address String representation of ipv4 address.
/// @return Parsed ip address packed as individual bytes in std::tuple.
/// @throws None (no-throw guarantee).
[[nodiscard]] auto ParseIp(std::string_view ip_address) noexcept -> ParsedIpType {
  auto parsed_ip_address = ParsedIpType{};
  sscanf(
    ip_address.data(),
    "%u.%u.%u.%u",
    &std::get<BytePosition::kFirst>(parsed_ip_address),
    &std::get<BytePosition::kSecond>(parsed_ip_address),
    &std::get<BytePosition::kThird>(parsed_ip_address),
    &std::get<BytePosition::kFourth>(parsed_ip_address)
  );
  return parsed_ip_address;
}

/// @internal
/// @brief Namespace containing implementation details.
/// @namespace __details
inline namespace __details {

/// @internal
/// @brief Prints the range to stdout.
/// @param[in] range Range to display.
/// @return None
/// @throws std::bad_alloc (if allocation fails).
auto DisplayRange(std::ranges::range auto&& range) -> void {
  std::size_t i{};
  for (auto const& value : std::forward<decltype(range)>(range)) {
    std::println("[{}] {}", i, value);
    ++i;
  }
}

}  // namespace __details

/// @brief Enumeration representing filter arguments required by tasks.
/// @enum FilterArgs
enum struct FilterArgs : unsigned char {
  kUnknown = 0,
  kTask1 = 1,
  kTask2FirstByte = 46,
  kTask2SecondByte = 70,
  kTask3 = 46
};

/// @brief Displays ip addresses to stdout.
/// @param[in] ip_addresses Vector of parsed ip addresses.
/// @return None.
/// @throws std::bad_alloc (if allocation fails).
auto Task1(const std::vector<ParsedIpType>& ip_addresses) -> void {
  std::println("[Task-1] Sorted range:");
  DisplayRange(ip_addresses);
}

/// @brief Displays sorted ip addresses to stdout.
/// @param[in] ip_addresses Vector of parsed ip addresses.
/// @return None.
/// @throws std::bad_alloc (if allocation fails).
auto Task2(const std::vector<ParsedIpType>& ip_addresses) -> void {
  auto filtered_range = ip_addresses | std::views::filter([] [[nodiscard]] (const auto& ip_address) noexcept -> bool {
                          return std::get<BytePosition::kFirst>(ip_address) == std::to_underlying(FilterArgs::kTask1);
                        });
  std::println("[Task-2] Sorted range (1, any, any, any):");
  DisplayRange(filtered_range);
}

/// @brief Displays sorted ip addresses to stdout.
/// @param[in] ip_addresses Vector of parsed ip addresses.
/// @return None.
/// @throws std::bad_alloc (if allocation fails).
/// @details Displays sorted range filtered with predicate.
auto Task3(const std::vector<ParsedIpType>& ip_addresses) -> void {
  auto filtered_range =
    ip_addresses | std::views::filter([] [[nodiscard]] (const auto& ip_address) noexcept -> bool {
      return std::get<BytePosition::kFirst>(ip_address) == std::to_underlying(FilterArgs::kTask2FirstByte) &&
             std::get<BytePosition::kSecond>(ip_address) == std::to_underlying(FilterArgs::kTask2SecondByte);
    });
  std::println("[Task-3] Sorted range (46, 70, any, any):");
  DisplayRange(filtered_range);
}

/// @brief Displays sorted ip addresses to stdout.
/// @param[in] ip_addresses Vector of parsed ip addresses.
/// @return None.
/// @throws std::bad_alloc (if allocation fails).
/// @details Displays sorted range filtered with predicate.
auto Task4(const std::vector<ParsedIpType>& ip_addresses) -> void {
  auto filtered_range = ip_addresses | std::views::filter([] [[nodiscard]] (const auto& ip_address) noexcept -> bool {
                          constexpr auto kFilterArg = std::to_underlying(FilterArgs::kTask3);
                          return std::get<BytePosition::kFirst>(ip_address) == kFilterArg ||
                                 std::get<BytePosition::kSecond>(ip_address) == kFilterArg ||
                                 std::get<BytePosition::kThird>(ip_address) == kFilterArg ||
                                 std::get<BytePosition::kFourth>(ip_address) == kFilterArg;
                        });
  std::println("[Task-4] Sorted range with any byte equal to 46:");
  DisplayRange(filtered_range);
}

}  // namespace lab::utility

namespace std {

/// @brief Full template specialization for `std::formatter`.
/// @class formatter
/// @details Full template specialization for `std::formatter` class to be used in `std::print` function.
template<>
struct formatter<lab::ParsedIpType, char> : public formatter<std::string> {
  [[nodiscard]] auto format(const lab::ParsedIpType& ip_address, std::format_context& context) const {
    auto ip_str = std::format(
      "{}.{}.{}.{}",
      std::get<lab::utility::BytePosition::kFirst>(ip_address),
      std::get<lab::utility::BytePosition::kSecond>(ip_address),
      std::get<lab::utility::BytePosition::kThird>(ip_address),
      std::get<lab::utility::BytePosition::kFourth>(ip_address)
    );
    return std::formatter<std::string>::format(ip_str, context);
  }
};

}  // namespace std
