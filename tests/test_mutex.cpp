#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cpp_util/mutex.hpp>

TEST_CASE("interface check", "[mutex]")
{
  util::mutex<int> test_m(10);

  test_m.apply([](auto& a) { a += 10; });
  REQUIRE(test_m.get() == 20);
}
