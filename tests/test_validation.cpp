#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cpp_util/validation.hpp>

namespace util::validation_tests {

template<class T>
auto test_func(util::valid<T> in)
{
    return *in;
}
} // namespace util::validation_tests

TEST_CASE("Validation Check", "[validation]")
{
    util::unary_predicate<int> gt_one = [](int a) { return a > 1; };
    util::unary_predicate<int> lt_hundred = [](int a) { return a < 100; };
    auto pred = util::pred_either(gt_one, lt_hundred);
    util::validator<int> int_validator(pred);

    auto valid_int = int_validator.validate(99);

    REQUIRE(*valid_int == 99);
    REQUIRE(util::validation_tests::test_func(valid_int) == 99);
}

TEST_CASE("Validation fail case", "[validation]")
{
    util::unary_predicate<int> pred = [](int a) { return a > 1; };
    util::validator<int> int_validator(pred);

    REQUIRE_THROWS_AS(int_validator.validate(0), std::invalid_argument);
}
