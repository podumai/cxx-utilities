#pragma once

#include <optional>
#include <string_view>
#include <tuple>
#include <vector>

namespace lab {

using ParsedIpType = std::tuple<unsigned, unsigned, unsigned, unsigned>;

namespace utility {

[[nodiscard]] extern auto ParseRow(std::string_view row) -> std::optional<std::vector<std::string_view>>;

[[nodiscard]] extern auto ParseIp(std::string_view ip_address) noexcept -> ParsedIpType;

extern auto Task1(const std::vector<ParsedIpType>& ip_addresses) -> void;

extern auto Task2(const std::vector<ParsedIpType>& ip_addresses) -> void;

extern auto Task3(const std::vector<ParsedIpType>& ip_addresses) -> void;

extern auto Task4(const std::vector<ParsedIpType>& ip_addresses) -> void;

}  // namespace utility

}  // namespace lab
