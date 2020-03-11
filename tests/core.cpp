#include <sys/ucontext.h>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "vml/vml.hpp"

TEMPLATE_TEST_CASE("vec1", "[vector][template]", uint8_t, uint16_t, uint32_t,
                   uint64_t, int8_t, int16_t, int32_t, int64_t, float, double) {

  SECTION("Constructor") {
    vml::vec1<TestType> a;
    REQUIRE(a == TestType());
    vml::vec1<TestType> b(TestType(5));
    REQUIRE(b == TestType(5));
  }
  SECTION("Access") {
    vml::vec1<TestType> a(TestType(5));
    REQUIRE(a.x == TestType(5));
    REQUIRE(a.r == TestType(5));
    REQUIRE(a[0] == TestType(5));
    REQUIRE(a == TestType(5));
    REQUIRE(static_cast<TestType>(a) == TestType(5));
    REQUIRE(static_cast<TestType>(a.x) == TestType(5));
    REQUIRE(static_cast<TestType>(a.r) == TestType(5));
    REQUIRE(static_cast<TestType>(a[0]) == TestType(5));
  }
  SECTION("Assignment") {
    vml::vec1<TestType> a;
    REQUIRE(a == TestType());
    a = TestType(5);
    REQUIRE(a == TestType(5));
    a.x = TestType(7);
    REQUIRE(a == TestType(7));
    a[0] = TestType(9);
    REQUIRE(a == TestType(9));
  }
  SECTION("Swizzle") {}
}

TEMPLATE_TEST_CASE("vec2", "[vector][template]", uint8_t, uint16_t, uint32_t,
                   uint64_t, int8_t, int16_t, int32_t, int64_t, float, double) {

  SECTION("Constructor") {
    vml::vec2<TestType> a;
    REQUIRE(a.x == TestType());
    REQUIRE(a.y == TestType());
    vml::vec2<TestType> b(TestType(5));
    REQUIRE(b.x == TestType(5));
    REQUIRE(b.y == TestType(5));
    vml::vec2<TestType> c(TestType(2), TestType(3));
    REQUIRE(c.x == TestType(2));
    REQUIRE(c.y == TestType(3));
  }
  SECTION("Access") {
    vml::vec2<TestType> a(TestType(2), TestType(3));
    REQUIRE(a.x == TestType(2));
    REQUIRE(a.r == TestType(2));
    REQUIRE(a[0] == TestType(2));
    REQUIRE(a.y == TestType(3));
    REQUIRE(a.g == TestType(3));
    REQUIRE(a[1] == TestType(3));
    REQUIRE(static_cast<TestType>(a.x) == TestType(2));
    REQUIRE(static_cast<TestType>(a.r) == TestType(2));
    REQUIRE(static_cast<TestType>(a[0]) == TestType(2));
    REQUIRE(static_cast<TestType>(a.y) == TestType(3));
    REQUIRE(static_cast<TestType>(a.g) == TestType(3));
    REQUIRE(static_cast<TestType>(a[1]) == TestType(3));
  }
  SECTION("Assignment") {
    vml::vec2<TestType> a;
    REQUIRE(a.x == TestType());
    REQUIRE(a.y == TestType());
    a.x = TestType(2);
    REQUIRE(a.x == TestType(2));
    a[0] = TestType(3);
    REQUIRE(a.x == TestType(3));
    REQUIRE(a.y == TestType());
    a.y = TestType(5);
    REQUIRE(a.y == TestType(5));
    a[1] = TestType(7);
    REQUIRE(a.y == TestType(7));
    REQUIRE(a.x == TestType(3));
  }
  SECTION("Swizzle") {
    vml::vec2<TestType> a(TestType(2), TestType(3));
    vml::vec2<TestType> b = a.yx;
    REQUIRE(b.x == TestType(3));
    REQUIRE(b.y == TestType(2));
    a.xy = a.yx;
    REQUIRE(a.x == TestType(3));
    REQUIRE(a.y == TestType(2));
  }
}
