#ifndef CPP_UTIL_SOCKET_ADDR_HPP
#define CPP_UTIL_SOCKET_ADDR_HPP

#include "ipv4.hpp"
#include <cstdint>
#include <variant>

namespace cpp_util {

class socket_addr {
public:
  using ip_address_t = std::variant<ipv4>;
  static auto from_ipv4(ipv4 ip_addr, uint16_t port) -> socket_addr
  {
    return socket_addr(ip_addr, port);
  }

  auto set_ipv4(ipv4 new_ip) -> void
  {
    ip_addr_ = new_ip;
  }

  auto set_port(uint16_t new_port) -> void
  {
    port_ = new_port;
  }

  [[nodiscard]] auto ip() const -> ip_address_t
  {
    return ip_addr_;
  }

  [[nodiscard]] auto port() const -> uint16_t
  {
    return port_;
  }

  [[nodiscard]] auto to_string() const -> std::string
  {
    auto PrintVisitor = [](const auto& ip) -> std::string { return ip.to_string(); };
    return std::visit(PrintVisitor, ip_addr_) + ':' + std::to_string(port_);
  }

private:
  socket_addr(ipv4 ip_addr, uint16_t port) : ip_addr_(ip_addr), port_(port)
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