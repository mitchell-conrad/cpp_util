#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cpp_util/string.hpp>

TEST_CASE("Intercalate Check")
{
  std::vector<std::string> test_case = {"a", "a", "a"};
  auto separator = std::string{", "};

  auto output = cpp_util::intercalate(test_case, separator);
  auto expected = std::string{"a, a, a"};

  REQUIRE(output == expected);
}

TEST_CASE("Flatten Check")
{
  std::vector<std::string> test_case = {"aaaaaa", "bbbbbb", "cccccc", "dddddd"};

  auto output = cpp_util::flatten(test_case);

  auto expected = std::string{"aaaaaabbbbbbccccccdddddd"};

  REQUIRE(output == expected);
}
