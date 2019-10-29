#ifndef CPP_UTIL_SOCKET_ADDR_HPP
#define CPP_UTIL_SOCKET_ADDR_HPP

#include "ipv4.hpp"
#include <cstdint>
#include <variant>

namespace cpp_util {

class socket_addr {
public:
  using ip_address_t = std::variant<ipv4>;
  [[nodiscard]] static auto from_string(const std::string& addr_string) -> socket_addr
  {
    // TODO: Sanitise this correctly.
    auto itr = addr_string.find_last_of(':');
    if(itr == std::string::npos) {
      throw std::invalid_argument("no port number found in given string");
    }
    auto&& substring = addr_string.substr(itr + 1);
    uint16_t port = std::stoi(substring);
    return socket_addr::from_ipv4(ipv4::from_string(addr_string.substr(0, itr)), port);
  }
  constexpr static auto from_ipv4(ipv4 ip_addr, uint16_t port) -> socket_addr
  {
    return socket_addr(ip_addr, port);
  }

  constexpr auto set_ipv4(ipv4 new_ip) -> void
  {
    ip_addr_ = new_ip;
  }

  constexpr auto set_port(uint16_t new_port) -> void
  {
    port_ = new_port;
  }

  [[nodiscard]] constexpr auto ip() const -> ip_address_t
  {
    return ip_addr_;
  }

  [[nodiscard]] constexpr auto port() const -> uint16_t
  {
    return port_;
  }

  [[nodiscard]] auto to_string() const -> std::string
  {
    auto PrintVisitor = [](const auto& ip) -> std::string { return ip.to_string(); };
    return std::visit(PrintVisitor, ip_addr_) + ':' + std::to_string(port_);
  }

private:
  constexpr socket_addr(ipv4 ip_addr, uint16_t port) : ip_addr_(ip_addr), port_(port)
  {
  }
  // TODO: Implement ipv6 support
  ip_address_t ip_addr_;
  uint16_t port_;
};

std::ostream& operator<<(std::ostream& out, const socket_addr& addr)
{
  return out << addr.to_string();
}
auto operator==(const socket_addr& a, const socket_addr& b)
{
  return (a.port() == b.port()) && (a.ip() == b.ip());
}

} // namespace cpp_util
#endif // CPP_UTIL_SOCKET_ADDR_HPP