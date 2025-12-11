#include <algorithm>
#include <cstdio>
#include <format>
#include <functional>
#include <print>
#include <ranges>
#include <tpu/utility.hpp>
#include <utility>

namespace lab::utility {

enum BytePosition : unsigned char { kUnknown = 0, kFirst = 0, kSecond = 1, kThird = 2, kFourth = 3 };

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

inline namespace __details {

auto DisplayRange(std::ranges::range auto&& range) -> void {
  for (auto&& [index, value] : std::views::enumerate(std::forward<decltype(range)>(range))) {
    std::println("[{}] {}", index, std::forward<decltype(value)>(value));
  }
}

}  // namespace __details

enum struct FilterArgs : unsigned char {
  kUnknown = 0,
  kTask1 = 1,
  kTask2FirstByte = 46,
  kTask2SecondByte = 70,
  kTask3 = 46
};

auto Task1(const std::vector<ParsedIpType>& ip_addresses) -> void {
  std::println("[Task-1] Sorted range:");
  DisplayRange(ip_addresses);
}

auto Task2(const std::vector<ParsedIpType>& ip_addresses) -> void {
  auto filtered_range = ip_addresses | std::views::filter([] [[nodiscard]] (const auto& ip_address) noexcept -> bool {
                          return std::get<BytePosition::kFirst>(ip_address) == std::to_underlying(FilterArgs::kTask1);
                        });
  std::println("[Task-2] Sorted range (1, any, any, any):");
  DisplayRange(filtered_range);
}

auto Task3(const std::vector<ParsedIpType>& ip_addresses) -> void {
  auto filtered_range =
    ip_addresses | std::views::filter([] [[nodiscard]] (const auto& ip_address) noexcept -> bool {
      return std::get<BytePosition::kFirst>(ip_address) == std::to_underlying(FilterArgs::kTask2FirstByte) &&
             std::get<BytePosition::kSecond>(ip_address) == std::to_underlying(FilterArgs::kTask2SecondByte);
    });
  std::println("[Task-3] Sorted range (46, 70, any, any):");
  DisplayRange(filtered_range);
}

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
