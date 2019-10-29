#include <cpp_util/string.hpp>
#include <numeric>

namespace cpp_util {

auto intercalate(const std::vector<std::string>& in, const std::string& separator) -> std::string
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

auto flatten(const std::vector<std::string>& in) -> std::string
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
} // namespace util
