#pragma once

#include <string>
#include <vector>

namespace util {
auto intercalate(std::vector<std::string> in, const std::string& separator) -> std::string;
} // namespace util
