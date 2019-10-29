#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cpp_util/predicate.hpp>

TEST_CASE("Conjunction Check")
{
  auto a = [](int in) { return in < 10; };
  auto b = [](int in) { return in > 1; };
  std::vector<util::unary_predicate<int>> vec = {a, b};
  auto predicate = util::pred_all(vec);

  REQUIRE(predicate(9));
  REQUIRE(!predicate(1));
}

TEST_CASE("Disjunction Check")
{
  auto a = [](int in) { return in < 10; };
  auto b = [](int in) { return in > 1; };

  std::vector<util::unary_predicate<int>> vec = {a, b};

  auto predicate = util::pred_any(vec);

  REQUIRE(predicate(0));
  REQUIRE(predicate(11));
}