#pragma once
#ifndef VML_HPP_
#define VML_HPP_

#include <cstdlib>
#include <type_traits>

namespace vml {
template <typename T, size_t M> struct vec;
template <typename T, size_t M, size_t N> struct mat;
template <typename T, size_t S, size_t N, size_t M> struct swizzle {
  T v[S];

  template <typename U = T, typename = typename std::enable_if<N == 1>>
  constexpr inline swizzle &operator=(const U &value) {
    v[M & 0XFF] = value;
    return *this;
  }
  template <size_t OtherS, size_t OtherM>
  constexpr inline swizzle &
  operator=(const swizzle<T, OtherS, N, OtherM> &other) {
    T tmp[N];
    for (size_t i = 0; i < N; ++i) {
      tmp[i] = other[i];
    }
    for (size_t i = 0; i < N; ++i) {
      v[(M >> (8 * i)) & 0xFF] = tmp[i];
    }
    return *this;
  }

  inline T &operator[](size_t i) { return v[(M >> (8 * i)) & 0xFF]; }
  constexpr inline const T &operator[](size_t i) const {
    return v[(M >> (8 * i)) & 0xFF];
  }
  template <typename U = T, typename = typename std::enable_if<
                                N == 1 && std::is_same<U, T>::value>>
  constexpr inline operator U &() {
    return v[0];
  }
  template <typename U = T, typename = typename std::enable_if<
                                N == 1 && std::is_same<U, T>::value>>
  constexpr inline operator const U &() const {
    return v[0];
  }

  constexpr inline operator vml::vec<T, N>() const {
    vml::vec<T, N> ret;
    for (size_t i = 0; i < N; ++i) {
      ret[i] = v[(M >> (8 * i)) & 0xFF];
    }
    return ret;
  }

  template <typename U = T, typename = typename std::enable_if<N == 1>>
  constexpr inline bool operator==(const U &rhs) const {
    return v[M & 0xFF] == rhs;
  }
};

template <typename T> struct vec<T, 1> {
  constexpr vec() : data{T()} {}
  constexpr vec(const T &x_) : data{x_} {}
  template <typename U, size_t N, typename = typename std::enable_if<(N >= 1)>>
  constexpr explicit vec(const vec<U, N> &v)
      : data{static_cast<T>(v.data[0])} {}

  constexpr const T &operator[](size_t i) const { return data[0]; }
  constexpr T &operator[](size_t i) { return data[0]; }

  constexpr operator T &() { return data[0]; }
  constexpr operator const T &() const { return data[0]; }

  union {
    T data[1];
    swizzle<T, 1, 1, 0x00> x, r;
  };
};
template <typename T> struct vec<T, 2> {
  constexpr vec() : data{T(), T()} {}
  constexpr vec(T *data_) : data(data_) {}
  constexpr vec(const T &x_, const T &y_) : data{x_, y_} {}
  constexpr explicit vec(const T &v_) : data{v_, v_} {}
  template <typename U, size_t N, typename = typename std::enable_if<(N >= 2)>>
  constexpr explicit vec(const vec<U, N> &v)
      : data{static_cast<T>(v.data[0]), static_cast<T>(v.data[1])} {}

  constexpr const T &operator[](size_t i) const { return data[0]; }
  constexpr T &operator[](size_t i) { return data[0]; }

  union {
    T data[2];
    swizzle<T, 2, 1, 0x00> x, r;
    swizzle<T, 2, 1, 0x01> y, g;
    swizzle<T, 2, 2, 0x0000> xx, rr;
    swizzle<T, 2, 2, 0x0001> yx, gr;
    swizzle<T, 2, 2, 0x0101> yy, gg;
    swizzle<T, 2, 2, 0x0100> xy, rg;
  };
};

template <typename T> using vec1 = vec<T, 1>;
template <typename T> using vec2 = vec<T, 2>;
template <typename T> using vec3 = vec<T, 3>;
template <typename T> using vec4 = vec<T, 4>;
typedef vec<float, 1> float1;
typedef vec<float, 2> float2;
typedef vec<float, 3> float3;
typedef vec<float, 4> float4;
typedef vec<double, 1> double1;
typedef vec<double, 2> double2;
typedef vec<double, 3> double3;
typedef vec<double, 4> double4;

} // namespace vml

#endif // VML_HPP_
