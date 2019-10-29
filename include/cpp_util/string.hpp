#ifndef CPP_UTIL_STRING_HPP
#define CPP_UTIL_STRING_HPP

#include <string>
#include <vector>

namespace cpp_util {
[[nodiscard]] auto
intercalate(const std::vector<std::string>& in, const std::string& separator) -> std::string;

[[nodiscard]] auto
flatten(const std::vector<std::string>& in) -> std::string;
} // namespace cpp_util

#endif // CPP_UTIL_STRING_HPP
