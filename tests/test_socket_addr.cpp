#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cpp_util/socket_addr.hpp>

TEST_CASE("to_string", "[socket_addr]")
{
  using namespace cpp_util;
  auto socket_addr = socket_addr::from_ipv4(ipv4::from_string("192.168.111."
                                                              "230"),
                                            20000);

  CHECK(socket_addr.to_string() == "192.168.111.230:20000");
}


// TODO: Test properly...