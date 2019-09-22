#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cpp_util/string.hpp>

TEST_CASE("Intercalate Check", "[string]")
{
  std::vector<std::string> test_case = {"a", "a", "a"};
  auto separator = std::string{", "};

  auto output = util::intercalate(test_case, separator);
  auto expected = std::string{"a, a, a"};

  REQUIRE(output == expected);
}

TEST_CASE("Flatten Check", "[string]")
{
  std::vector<std::string> test_case = {"aaaaaa", "bbbbbb", "cccccc", "dddddd"};

  auto output = util::flatten(test_case);

  auto expected = std::string{"aaaaaabbbbbbccccccdddddd"};

  REQUIRE(output == expected);
}
