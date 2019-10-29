#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cpp_util/socket_addr.hpp>

TEST_CASE("to_string")
{
  using namespace cpp_util;
  constexpr auto socket_addr = socket_addr::from_ipv4(ipv4::from_ints(192, 168, 111, 230), 20000);

  CHECK(socket_addr.to_string() == "192.168.111.230:20000");
}

TEST_CASE("from_string")
{
  using namespace cpp_util;
  auto socket_addr = socket_addr::from_string("192.168.1.99:12345");
  CHECK(socket_addr.to_string() == "192.168.1.99:12345");

  CHECK_THROWS_AS(socket_addr::from_string("192.168.111.230:adsf"), std::invalid_argument);
  // TODO: Get these tests passing by improving sanitation.
  /* CHECK_THROWS_AS(socket_addr::from_string("192.168.111.230"), std::invalid_argument);
     CHECK_THROWS_AS(socket_addr::from_string("192.168.111.230:1111111111"), std::invalid_argument);
     CHECK_THROWS_AS(socket_addr::from_string("192.168.111.230:123adsf"), std::invalid_argument);
  */
}

// TODO: Test properly...