#pragma once

#include <string>
#include <vector>

namespace util {
auto intercalate(const std::vector<std::string>& in, const std::string& separator) -> std::string;
auto flatten(const std::vector<std::string>& in) -> std::string;
} // namespace util
