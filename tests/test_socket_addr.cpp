#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cpp_util/socket_addr.hpp>

TEST_CASE("to_string")
{
  using namespace cpp_util;
  constexpr auto socket_addr = socket_addr::from_ipv4(ipv4::from_ints(192, 168, 111, 230), 20000);

  CHECK(socket_addr.to_string() == "192.168.111.230:20000");
}

// TODO: Test properly...