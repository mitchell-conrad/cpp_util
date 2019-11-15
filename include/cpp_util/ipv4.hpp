#ifndef CPP_UTIL_IPV4_HPP
#define CPP_UTIL_IPV4_HPP
#include <array>
#include <regex>
#include <string>

namespace cpp_util {

class ipv4 {
public:
  [[nodiscard]] static auto
  from_string(const std::string_view addr_string) -> ipv4
  {
    // Validate ipv4 address format
    // Regex matches nnn.nnn.nnn.nnn, where n is a numeral and the number of numerals per octet is
    //  1-3
    const std::regex addr_check{R"--(\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b)--"};
    if(!std::regex_match(addr_string.begin(), addr_string.end(), addr_check)) {
      throw std::invalid_argument("invalid ip addr string");
    }
    std::array<uint8_t, 4> octets{};

    // Get ourselves a mutable copy of our string view
    auto current_substr = addr_string;
    for(auto& octet : octets) {
      char* current_ptr;
      auto parsed = std::strtol(current_substr.data(), &current_ptr, 10);

      // Check that parsed long exists inside valid uint8_t range
      if(parsed > 255 || parsed < 0) {
        throw std::invalid_argument("ip address string has octet out of range 0 <= x <= 255");
      }
      octet = parsed;

      // Cut parsed chars off front of str
      current_substr.remove_prefix(std::distance(current_substr.data(), (const char*)current_ptr));
      // Cut '.' off front of str
      current_substr.remove_prefix(1);
    }

    return ipv4::from_array(octets);
  }

  [[nodiscard]] constexpr static auto
  from_ints(const uint8_t a, const uint8_t b, const uint8_t c, const uint8_t d) -> ipv4
  {
    return ipv4(a, b, c, d);
  };

  [[nodiscard]] constexpr static auto
  from_array(const std::array<uint8_t, 4>& array) -> ipv4
  {
    // This constructor enforces its own invariants!
    return ipv4(array[0], array[1], array[2], array[3]);
  }

  [[nodiscard]] constexpr static auto
  unspecified() -> ipv4
  {
    return ipv4(0, 0, 0, 0);
  }

  [[nodiscard]] constexpr static auto
  broadcast() -> ipv4
  {
    return ipv4(255, 255, 255, 255);
  }

  [[nodiscard]] constexpr static auto
  localhost() -> ipv4
  {
    return ipv4(127, 0, 0, 1);
  }

  [[nodiscard]] constexpr auto
  octets() const -> std::array<uint8_t, 4>
  {
    return addr_;
  }

  [[nodiscard]] auto
  to_string() const -> std::string
  {
    // TODO: Optimise this...
    return std::string{std::to_string(addr_[0]) + '.' + std::to_string(addr_[1]) + '.'
                       + std::to_string(addr_[2]) + '.' + std::to_string(addr_[3])};
  }

private:
  constexpr ipv4(const uint8_t a, const uint8_t b, const uint8_t c, const uint8_t d) :
    addr_{a, b, c, d}
  {
  }

  std::array<uint8_t, 4> addr_;
};

inline auto
operator<<(std::ostream& out, const ipv4& addr) -> std::ostream&
{
  return out << addr.to_string();
}
inline auto
operator==(const ipv4& a, const ipv4& b)
{
  return a.octets() == b.octets();
}

} // namespace cpp_util

#endif // CPP_UTIL_IPV4_HPP
