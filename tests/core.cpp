#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "vml/vml.hpp"

TEMPLATE_TEST_CASE("vec1", "[vector][template]", uint8_t, uint16_t, uint32_t,
                   uint64_t, int8_t, int16_t, int32_t, int64_t, float, double) {
  vml::vec<TestType, 2> a(TestType(2), TestType(3));
  REQUIRE(sizeof(a.x) == sizeof(TestType) * 2);
  REQUIRE(sizeof(a.xx) == sizeof(TestType) * 2);
  REQUIRE(sizeof(a.xy) == sizeof(TestType) * 2);
  REQUIRE(sizeof(a.yx) == sizeof(TestType) * 2);
  REQUIRE(sizeof(a.yy) == sizeof(TestType) * 2);
  REQUIRE(a.x == TestType(2));
}

TEMPLATE_TEST_CASE("vec2", "[vector][template]", uint8_t, uint16_t, uint32_t,
                   uint64_t, int8_t, int16_t, int32_t, int64_t, float, double) {

}
