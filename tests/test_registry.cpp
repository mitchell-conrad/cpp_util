#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cpp_util/registry.hpp>
#include <iostream>
#include <memory>

TEST_CASE("Interface check")
{
  cpp_util::registry<int> reg;
  auto id = reg.append(1);
  auto val = reg.get(id);
  reg.erase(id);
  reg.for_each([](int i) {});
}

TEST_CASE("Unique Ptr")
{
  cpp_util::registry<std::unique_ptr<int>> reg;

  auto id = reg.append(std::make_unique<int>(1));

  auto& int_ref = reg.get(id);

  REQUIRE(*int_ref == 1);

  reg.erase(id);

  REQUIRE_THROWS_AS(reg.get(id), std::out_of_range);
}

TEST_CASE("Add Erase")
{
  cpp_util::registry<std::string> reg;

  auto erase_id = reg.append("erase string");
  auto id = reg.append("keep string");

  reg.erase(erase_id);

  REQUIRE(reg.get(id) == "keep string");
  REQUIRE_THROWS_AS(reg.get(erase_id), std::out_of_range);
  REQUIRE(reg.get(id) == "keep string");
}
