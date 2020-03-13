#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include "vml/vml.hpp"

TEMPLATE_TEST_CASE("benchmark", "[vector][template]", float, double) {
  std::array<vml::tvec3<TestType>, 1000> a, b, c;
  for (size_t i = 0; i < 1000; ++i) {
    a[i] = vml::tvec3<TestType>(TestType(2 * i + 1), TestType(4 * i + 1),
                                TestType(6 * i + 1));
    b[i] = vml::tvec3<TestType>(TestType(3 * i + 1), TestType(5 * i + 1),
                                TestType(7 * i + 1));
  }
  BENCHMARK("+ [CPU]") {
    for (size_t i = 0; i < 1000; ++i) {
      c[i] = a[i] + b[i];
    }
  };
  BENCHMARK("- [CPU]") {
    for (size_t i = 0; i < 1000; ++i) {
      c[i] = b[i] - a[i];
    }
  };
  BENCHMARK("* [CPU]") {
    for (size_t i = 0; i < 1000; ++i) {
      c[i] = a[i] * b[i];
    }
  };
  BENCHMARK("/ [CPU]") {
    for (size_t i = 0; i < 1000; ++i) {
      c[i] = a[i] / a[i];
    }
  };
#ifdef __USE_OPENACC__
  BENCHMARK("+ [GPU]") {
#pragma omp parallel for schedule(dynamic, 128) shared(a, b, c)
    for (size_t i = 0; i < 1000; ++i) {
      c[i] = a[i] + b[i];
    }
  };
  BENCHMARK("- [GPU]") {
#pragma omp parallel for schedule(dynamic, 128) shared(a, b, c)
    for (size_t i = 0; i < 1000; ++i) {
      c[i] = b[i] - a[i];
    }
  };
  BENCHMARK("* [GPU]") {
#pragma omp parallel for schedule(dynamic, 128) shared(a, b, c)
    for (size_t i = 0; i < 1000; ++i) {
      c[i] = a[i] * b[i];
    }
  };
  BENCHMARK("/ [GPU]") {
#pragma omp parallel for schedule(dynamic, 128) shared(a, b, c)
    for (size_t i = 0; i < 1000; ++i) {
      c[i] = a[i] / a[i];
    }
  };
#endif // __USE_OPENACC__
}
