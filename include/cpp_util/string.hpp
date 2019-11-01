#ifndef CPP_UTIL_STRING_HPP
#define CPP_UTIL_STRING_HPP

#include <cctype>
#include <numeric>
#include <string>
#include <vector>

namespace cpp_util {
[[nodiscard]] auto
intercalate(const std::vector<std::string>& in, std::string_view separator) -> std::string
{
  auto it = std::begin(in);
  std::string out = *it;

  it = std::next(it);
  while(it != std::end(in)) {
    out += separator;
    out += *it;
    it = std::next(it);
  }
  return out;
}

[[nodiscard]] auto
flatten(const std::vector<std::string>& in) -> std::string
{
  // Calculate pre-reserve size
  auto reserve_size = std::accumulate(in.begin(), in.end(), 0, [](int current, const auto& str) {
    return current + str.size();
  });

  // Pre-reserve output string
  std::string out{};
  out.reserve(reserve_size);

  auto it = std::begin(in);
  while(it != std::end(in)) {
    out += *it;
    it = std::next(it);
  }
  return out;
}

[[nodiscard]] auto
to_lower(const std::string_view in) -> std::string
{
  std::string out{in};
  std::transform(out.begin(), out.end(), out.begin(),
                 [](unsigned char c) -> unsigned char { return std::tolower(c); });
  return out;
}

[[nodiscard]] auto
to_upper(const std::string_view in) -> std::string
{
  std::string out{in};
  std::transform(out.begin(), out.end(), out.begin(),
                 [](unsigned char c) -> unsigned char { return std::toupper(c); });
  return out;
}

} // namespace cpp_util

#endif // CPP_UTIL_STRING_HPP
