#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include "vml/vml.hpp"

TEMPLATE_TEST_CASE("vec1", "[vector][template]", uint8_t, uint16_t, uint32_t,
                   uint64_t, int8_t, int16_t, int32_t, int64_t, float, double) {

  SECTION("Constructor") {
    vml::tvec1<TestType> a;
    REQUIRE(a == TestType());
    vml::tvec1<TestType> b(TestType(5));
    REQUIRE(b == TestType(5));
  }
  SECTION("Access") {
    vml::tvec1<TestType> a(TestType(5));
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
    vml::tvec1<TestType> a;
    REQUIRE(a == TestType());
    a = TestType(5);
    REQUIRE(a == TestType(5));
    a.x = TestType(7);
    REQUIRE(a == TestType(7));
    a[0] = TestType(9);
    REQUIRE(a == TestType(9));
  }
  SECTION("Comparison") {
    vml::tvec1<TestType> a(TestType(3)), b(TestType(5));
    REQUIRE(a != b);
    REQUIRE(a == a);
  }
  SECTION("Operators") {
    vml::tvec1<TestType> a(TestType(2)), b(TestType(3));
    REQUIRE(a == TestType(2));
    REQUIRE(b == TestType(3));
    a += b;
    REQUIRE(a == TestType(5));
    REQUIRE(b == TestType(3));
    a *= b;
    REQUIRE(a == TestType(15));
    REQUIRE(b == TestType(3));
    a -= b;
    REQUIRE(a == TestType(12));
    REQUIRE(b == TestType(3));
    a /= b;
    REQUIRE(a == TestType(4));
    REQUIRE(b == TestType(3));
    a += TestType(2);
    REQUIRE(a == TestType(6));
    a -= TestType(3);
    REQUIRE(a == TestType(3));
    a *= TestType(5);
    REQUIRE(a == TestType(15));
    a /= TestType(5);
    REQUIRE(a == TestType(3));
  }
  SECTION("Swizzle") {}
  SECTION("Fmt") {
    vml::tvec1<TestType> a(TestType(2));
    REQUIRE(vml::fmt(a) == std::to_string(TestType(2)));
  }
}

TEMPLATE_TEST_CASE("vec2", "[vector][template]", uint8_t, uint16_t, uint32_t,
                   uint64_t, int8_t, int32_t, int64_t, float, double) {

  SECTION("Constructor") {
    vml::tvec2<TestType> a;
    REQUIRE(a.x == TestType());
    REQUIRE(a.y == TestType());
    vml::tvec2<TestType> b(TestType(5));
    REQUIRE(b.x == TestType(5));
    REQUIRE(b.y == TestType(5));
    vml::tvec2<TestType> c(TestType(2), TestType(3));
    REQUIRE(c.x == TestType(2));
    REQUIRE(c.y == TestType(3));
  }
  SECTION("Access") {
    vml::tvec2<TestType> a(TestType(2), TestType(3));
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
    vml::tvec2<TestType> a;
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
  SECTION("Comparison") {
    vml::tvec2<TestType> a(TestType(2), TestType(3)),
        b(TestType(5), TestType(7));
    REQUIRE(a != b);
    REQUIRE(a == a);
  }
  SECTION("Operators") {
    vml::tvec2<TestType> a(TestType(2), TestType(3)),
        b(TestType(5), TestType(7));
    REQUIRE(a == vml::tvec2<TestType>(TestType(2), TestType(3)));
    REQUIRE(b == vml::tvec2<TestType>(TestType(5), TestType(7)));
    a += b;
    REQUIRE(a == vml::tvec2<TestType>(TestType(7), TestType(10)));
    REQUIRE(b == vml::tvec2<TestType>(TestType(5), TestType(7)));
    a *= b;
    REQUIRE(a == vml::tvec2<TestType>(TestType(35), TestType(70)));
    REQUIRE(b == vml::tvec2<TestType>(TestType(5), TestType(7)));
    a -= b;
    REQUIRE(a == vml::tvec2<TestType>(TestType(30), TestType(63)));
    REQUIRE(b == vml::tvec2<TestType>(TestType(5), TestType(7)));
    a /= b;
    REQUIRE(a == vml::tvec2<TestType>(TestType(6), TestType(9)));
    REQUIRE(b == vml::tvec2<TestType>(TestType(5), TestType(7)));
    a += TestType(2);
    REQUIRE(a == vml::tvec2<TestType>(TestType(8), TestType(11)));
    a -= TestType(3);
    REQUIRE(a == vml::tvec2<TestType>(TestType(5), TestType(8)));
    a *= TestType(2);
    REQUIRE(a == vml::tvec2<TestType>(TestType(10), TestType(16)));
    a /= TestType(5);
    REQUIRE(a == vml::tvec2<TestType>(TestType(2), TestType(3.2)));
  }
  SECTION("Swizzle") {
    vml::tvec2<TestType> a(TestType(2), TestType(3));
    vml::tvec2<TestType> b = a.yx;
    REQUIRE(b.x == TestType(3));
    REQUIRE(b.y == TestType(2));
    a.xy = a.yx;
    REQUIRE(a.x == TestType(3));
    REQUIRE(a.y == TestType(2));
    a.xy += a.xx;
    REQUIRE(a.x == TestType(6));
    REQUIRE(a.y == TestType(5));
    a.xy *= a.yy;
    REQUIRE(a.x == TestType(30));
    REQUIRE(a.y == TestType(25));
    a.xy /= a.xy;
    REQUIRE(a.x == TestType(1));
    REQUIRE(a.y == TestType(1));
    a.xy -= a.xy;
    REQUIRE(a.x == TestType(0));
    REQUIRE(a.y == TestType(0));
  }
}
