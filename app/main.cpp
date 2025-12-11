#include <algorithm>
#include <exception>
#include <fstream>
#include <functional>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <tpu/utility.hpp>
#include <vector>

auto main(int argc, char* argv[]) -> int {
  if (argc != 2 || !std::string_view{argv[1]}.ends_with(".tsv")) {
    std::println(stderr, "usage: ip-filter <filename>.tsv");
    return 1;
  }
  try {
    auto ips = std::ifstream{argv[1]};
    if (!ips.is_open()) {
      std::println(stderr, "[ERROR] unable to open file: ip_filter.tsv");
      return 1;
    }
    auto ip_adresses = std::vector<lab::ParsedIpType>{};
    for (auto buffer = std::string{}; std::getline(ips, buffer);) {
      auto parsed_row = lab::utility::ParseRow(buffer);
      if (!parsed_row.has_value()) {
        std::println(stderr, "[ERROR] Parsing row failed: {}", buffer);
        continue;
      }
      auto parsed_ip = lab::utility::ParseIp(parsed_row->front());
      ip_adresses.push_back(parsed_ip);
    }

    std::ranges::sort(ip_adresses, std::greater<typename decltype(ip_adresses)::value_type>{});
    lab::utility::Task1(ip_adresses);
    lab::utility::Task2(ip_adresses);
    lab::utility::Task3(ip_adresses);
    lab::utility::Task4(ip_adresses);
  } catch (const std::exception& error) {
    std::println(stderr, "[ERROR] message: {}", error.what());
    return 1;
  } catch (...) {
    std::println(stderr, "[ERROR] Unknown exception type.");
    return 1;
  }
  return 0;
}
