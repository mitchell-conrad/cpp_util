#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cpp_util/validation.hpp>

namespace util::validation_tests {

enum class int_validators {
  int_gt1_lt100,
  int_gt1,
};

template<class T>
auto test_func(util::valid<int_validators::int_gt1_lt100, T> in)
{
  return *in;
}

TEST_CASE("Validation Check")
{
  util::unary_predicate<int> gt_one = [](int a) { return a > 1; };
  util::unary_predicate<int> lt_hundred = [](int a) { return a < 100; };
  auto pred = util::pred_either(gt_one, lt_hundred);
  util::validator<int_validators::int_gt1_lt100, int> int_validator(pred);

  auto valid_int = int_validator.validate(99);

  REQUIRE(*valid_int == 99);
  REQUIRE(util::validation_tests::test_func(valid_int) == 99);
}

TEST_CASE("Validation fail case")
{
  util::unary_predicate<int> pred = [](int a) { return a > 1; };
  util::validator<int_validators::int_gt1, int> int_validator(pred);

  REQUIRE_THROWS_AS(int_validator.validate(0), std::invalid_argument);
}

} // namespace util::validation_tests
