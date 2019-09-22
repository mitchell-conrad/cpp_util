#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cpp_util/registry.hpp>
#include <iostream>
#include <memory>

TEST_CASE("Interface check", "[registry]")
{
  util::registry<int> reg;
  auto id = reg.append(1);
  auto val = reg.get(id);
  reg.erase(id);
  reg.for_each([](int i) {});
}

TEST_CASE("Unique Ptr", "[registry]")
{
  util::registry<std::unique_ptr<int>> reg;

  auto id = reg.append(std::make_unique<int>(1));

  auto& int_ref = reg.get(id);

  REQUIRE(*int_ref == 1);

  reg.erase(id);

  REQUIRE_THROWS_AS(reg.get(id), std::out_of_range);
}

TEST_CASE("Add Erase", "[registry]")
{
  util::registry<std::string> reg;

  auto erase_id = reg.append("erase string");
  auto id = reg.append("keep string");

  reg.erase(erase_id);

  REQUIRE(reg.get(id) == "keep string");
  REQUIRE_THROWS_AS(reg.get(erase_id), std::out_of_range);
  REQUIRE(reg.get(id) == "keep string");
}
