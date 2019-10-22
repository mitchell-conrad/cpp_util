#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cpp_util/ipv4.hpp>

TEST_CASE("initialisation test", "[ipv4]")
{
  auto test = cpp_util::ipv4::from_ints(0, 0, 0, 0);
  CHECK(test == cpp_util::ipv4::unspecified());
}

TEST_CASE("from_string", "[ipv4]")
{
  auto test = cpp_util::ipv4::from_string("192.168.111.230");
  CHECK(test == cpp_util::ipv4::from_ints(192, 168, 111, 230));

  auto short_test = cpp_util::ipv4::from_string("1.1.1.1");
  CHECK(short_test == cpp_util::ipv4::from_ints(1, 1, 1, 1));

  CHECK_THROWS_AS(cpp_util::ipv4::from_string("asdf"), std::invalid_argument);
  CHECK_THROWS_AS(cpp_util::ipv4::from_string("192.168.111.230.123"), std::invalid_argument);
  CHECK_THROWS_AS(cpp_util::ipv4::from_string("300.168.111.230"), std::invalid_argument);
  CHECK_THROWS_AS(cpp_util::ipv4::from_string("200.168.111"), std::invalid_argument);
  CHECK_THROWS_AS(cpp_util::ipv4::from_string("192.168.111.2a1"), std::invalid_argument);
}

TEST_CASE("ip_constants", "[ipv4]")
{
  auto localhost = cpp_util::ipv4::localhost();
  CHECK(localhost == cpp_util::ipv4::from_ints(127, 0, 0, 1));

  auto broadcast = cpp_util::ipv4::broadcast();
  CHECK(broadcast == cpp_util::ipv4::from_ints(255, 255, 255, 255));

  auto unspecified = cpp_util::ipv4::unspecified();
  CHECK(unspecified == cpp_util::ipv4::from_ints(0, 0, 0, 0));
}

TEST_CASE("ostream operator", "[ipv4]")
{
  auto unspecified = cpp_util::ipv4::unspecified();
  std::ostringstream stream;
  stream << unspecified;
  CHECK(stream.str() == "0.0.0.0");
}

TEST_CASE("to_string", "[ipv4]")
{
  auto unspecified = cpp_util::ipv4::unspecified();
  CHECK(unspecified.to_string() == "0.0.0.0");

  std::string test_string{"192.168.111.230"};
  CHECK(cpp_util::ipv4::from_string(test_string).to_string() == test_string);
}