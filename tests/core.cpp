#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include "vml/vml.hpp"

TEMPLATE_TEST_CASE("vec1", "[vector][template]", float) {
  vml::matrix<TestType> a(2, 2, 1.0, 2.0, 3.0, 4.0);
  REQUIRE(a[0][0] == 1.0);
}
