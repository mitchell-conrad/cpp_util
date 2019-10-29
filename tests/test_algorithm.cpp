#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cpp_util/algorithm.hpp>

TEST_CASE("All Of")
{
  using namespace cpp_util;
  REQUIRE(all_of(1, 2, 3) > 0);
  REQUIRE(!(all_of(-1, -2, -3) > 0));
}

TEST_CASE("Any Of")
{
  using namespace cpp_util;
  REQUIRE(any_of(1, 2, 3) == 1);
  REQUIRE(any_of(2, 2, 1) == 1);
}

TEST_CASE("Compound")
{
  using namespace cpp_util;
  REQUIRE(less_than(any_of(1, 2))(2) == false);

  std::vector<int> s{10, 12, 3, 11};
  auto i = std::find_if(s.begin(), s.end(), less_than(any_of(1, 2, 3, 4)));
  REQUIRE(std::distance(s.begin(), i) == 2);

  // TODO: Add other comparison operators
  //    i = std::find_if(s.begin(), s.end(), util::not_equal_to(util::any_of(1,2,3,4)));
  //    REQUIRE(std::distance(s.begin(), i) == 0);
}