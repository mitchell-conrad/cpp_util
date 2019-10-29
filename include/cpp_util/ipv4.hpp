#ifndef CPP_UTIL_IPV4_HPP
#define CPP_UTIL_IPV4_HPP
#include <array>
#include <string>

namespace cpp_util {

class ipv4 {
public:
  [[nodiscard]] static auto
  from_string(const std::string& addr_string) -> ipv4
  {
    if(addr_string.length() > 15) {
      throw std::invalid_argument("ip address string given is longer than 15 chars");
    }
    std::array<uint8_t, 4> octets{};

    size_t idx{};
    for(int i = 0; i < 4; ++i) {
      size_t processed{};
      auto parsed = std::stoi(addr_string.substr(idx), &processed, 10);
      if(parsed > 255 || parsed < 0) {
        throw std::invalid_argument("ip address string has octet out of range 0 <= x <= 255");
      }

      // Skip however many chars we've successfully stoi'd
      idx += processed;

      // If we're expecting another '.', check that we get one
      if(i != 3 && (idx >= addr_string.length() || addr_string.at(idx) != '.')) {
        throw std::invalid_argument("ip address string given is invalid");
      }

      // If we're processing our last octet, check that we've processed the entire octet
      if(i == 3 && idx != addr_string.length()) {
        throw std::invalid_argument("ip address string given is invalid");
      }
      // Skip '.'
      idx++;
      octets[i] = parsed;
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

auto
operator<<(std::ostream& out, const ipv4& addr) -> std::ostream&
{
  return out << addr.to_string();
}
auto
operator==(const ipv4& a, const ipv4& b)
{
  return a.octets() == b.octets();
}

} // namespace cpp_util

#endif // CPP_UTIL_IPV4_HPP
