#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cpp_util/algorithm.hpp>

TEST_CASE("All Of", "[algorithm]")
{
    REQUIRE(util::all_of(1, 2, 3) > 0);
    REQUIRE(!(util::all_of(-1, -2, -3) > 0));
}

TEST_CASE("Any Of", "[algorithm]")
{
    REQUIRE(util::any_of(1, 2, 3) == 1);
    REQUIRE(util::any_of(2, 2, 1) == 1);
}

TEST_CASE("Compound", "[algorithm]")
{
    REQUIRE(util::less_than(util::any_of(1, 2))(2) == false);

    std::vector<int> s{10, 12, 3, 11};
    auto i = std::find_if(s.begin(), s.end(), util::less_than(util::any_of(1, 2, 3, 4)));
    REQUIRE(std::distance(s.begin(), i) == 2);

    // TODO: Add other comparison operators
    //    i = std::find_if(s.begin(), s.end(), util::not_equal_to(util::any_of(1,2,3,4)));
    //    REQUIRE(std::distance(s.begin(), i) == 0);
}