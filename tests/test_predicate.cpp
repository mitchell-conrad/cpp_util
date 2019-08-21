#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cpp_util/predicate.hpp>

TEST_CASE("Conjunction Check", "[predicate]")
{
    auto a = [](int in) { return in < 10; };
    auto b = [](int in) { return in > 1; };
    auto unit = util::true_id<int>();
    std::vector<util::unary_predicate<int>> vec = {a, b};
    auto pred = util::pred_all(vec);

    REQUIRE(pred(9));
    REQUIRE(!pred(1));
}