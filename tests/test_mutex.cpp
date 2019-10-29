#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cpp_util/mutex.hpp>

TEST_CASE("interface check")
{
  util::mutex<int> test_m(10);

  test_m.apply([](auto& a) { a += 10; });
  REQUIRE(test_m.get() == 20);
}
