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
  template <size_t OtherS, size_t OtherM>
  constexpr inline swizzle &operator=(const swizzle<T, OtherS, N, OtherM> &v_) {
    T tmp[N];
    for (std::size_t i = 0; i < N; ++i) {
      tmp[i] = v_.v[(OtherM >> (8 * i)) & 0XFF];
    }
    for (std::size_t j = 0; j < N; ++j) {
      v[(M >> (8 * j)) & 0xFF] = tmp[j];
    }
    return *this;
  }
  constexpr inline T &operator[](size_t i) { return v[(M >> (8 * i)) & 0xFF]; }
  constexpr inline const T &operator[](size_t i) const {
    return v[(M >> (8 * i)) & 0xFF];
  }
  constexpr inline operator vml::vec<T, N>() const {
    vml::vec<T, N> ret;
    for (size_t i = 0; i < N; ++i)
      ret[i] = v[(M >> (8 * i)) & 0xFF];
    return ret;
  }
};

template <typename T, size_t S, size_t M> struct swizzle<T, S, 1, M> {
  T v[S];

  constexpr inline swizzle &operator=(const T &v_) {
    v[M & 0xFF] = v_;
    return *this;
  }

  constexpr inline T &operator[](size_t i) { return v[(M >> (8 * i)) & 0xFF]; }
  constexpr inline const T &operator[](size_t i) const {
    return v[(M >> (8 * i)) & 0xFF];
  }
  constexpr inline operator vml::vec<T, 1>() const {
    return vml::vec<T, 1>(v[M & 0xFF]);
  }
  constexpr inline operator T &() { return v[M & 0xFF]; }
  constexpr inline operator const T &() const { return v[M & 0xFF]; }
};

template <typename T> struct vec<T, 1> {
  constexpr vec() : data{T()} {}
  constexpr vec(const T &x_) : data{x_} {}
  template <typename U, size_t N,
            typename std::enable_if<(N >= 1)>::type * = nullptr>
  constexpr explicit vec(const vec<U, N> &v)
      : data{static_cast<T>(v.data[0])} {}

  constexpr const T &operator[](size_t i) const { return data[0]; }
  constexpr T &operator[](size_t i) { return data[0]; }

  constexpr operator T &() { return data[0]; }
  constexpr operator const T &() const { return data[0]; }

  union {
    T data[1];
    swizzle<T, 1, 1, 0x00> x, r;
    swizzle<T, 1, 2, 0x0000> xx, rr;
    swizzle<T, 1, 3, 0x000000> xxx, rrr;
    swizzle<T, 1, 4, 0x00000000> xxxx, rrrr;
  };
};
template <typename T> struct vec<T, 2> {
  constexpr vec() : data{T(), T()} {}
  constexpr vec(const T &x_, const T &y_) : data{x_, y_} {}
  constexpr explicit vec(const T &v_) : data{v_, v_} {}
  template <typename U, size_t N,
            typename std::enable_if<(N >= 2)>::type * = nullptr>
  constexpr explicit vec(const vec<U, N> &v)
      : data{static_cast<T>(v.data[0]), static_cast<T>(v.data[1])} {}

  constexpr const T &operator[](size_t i) const { return data[i]; }
  constexpr T &operator[](size_t i) { return data[i]; }

  union {
    T data[2];
    swizzle<T, 2, 1, 0x00> x, r;
    swizzle<T, 2, 1, 0x01> y, g;
    swizzle<T, 2, 2, 0x0000> xx, rr;
    swizzle<T, 2, 2, 0x0001> yx, gr;
    swizzle<T, 2, 2, 0x0100> xy, rg;
    swizzle<T, 2, 2, 0x0101> yy, gg;
    swizzle<T, 2, 3, 0x000000> xxx, rrr;
    swizzle<T, 2, 3, 0x000100> xyx, rgr;
    swizzle<T, 2, 3, 0x010000> xxy, rrg;
    swizzle<T, 2, 3, 0x010100> xyy, rgg;
    swizzle<T, 2, 3, 0x000001> yxx, grr;
    swizzle<T, 2, 3, 0x000101> yyx, ggr;
    swizzle<T, 2, 3, 0x010001> yxy, grg;
    swizzle<T, 2, 3, 0x010101> yyy, ggg;
    swizzle<T, 2, 4, 0x00000000> xxxx, rrrr;
    swizzle<T, 2, 4, 0x00010000> xxyx, rrgr;
    swizzle<T, 2, 4, 0x01000000> xxxy, rrrg;
    swizzle<T, 2, 4, 0x01010000> xxyy, rrgg;
    swizzle<T, 2, 4, 0x00000100> xyxx, rgrr;
    swizzle<T, 2, 4, 0x00010100> xyyx, rggr;
    swizzle<T, 2, 4, 0x01000100> xyxy, rgrg;
    swizzle<T, 2, 4, 0x01010100> xyyy, rggg;
    swizzle<T, 2, 4, 0x00000001> yxxx, grrr;
    swizzle<T, 2, 4, 0x00010001> yxyx, grgr;
    swizzle<T, 2, 4, 0x01000001> yxxy, grrg;
    swizzle<T, 2, 4, 0x01010001> yxyy, grgg;
    swizzle<T, 2, 4, 0x00000101> yyxx, ggrr;
    swizzle<T, 2, 4, 0x00010101> yyyx, gggr;
    swizzle<T, 2, 4, 0x01000101> yyxy, ggrg;
    swizzle<T, 2, 4, 0x01010101> yyyy, gggg;
  };
};
template <typename T> struct vec<T, 3> {
  constexpr vec() : data{T(), T(), T()} {}
  constexpr vec(const T &x_, const T &y_, const T &z_) : data{x_, y_, z_} {}
  constexpr explicit vec(const T &v_) : data{v_, v_, v_} {}
  template <typename U, size_t N,
            typename std::enable_if<(N >= 3)>::type * = nullptr>
  constexpr explicit vec(const vec<U, N> &v)
      : data{static_cast<T>(v.data[0]), static_cast<T>(v.data[1]),
             static_cast<T>(v.data[2])} {}

  constexpr const T &operator[](size_t i) const { return data[i]; }
  constexpr T &operator[](size_t i) { return data[i]; }

  union {
    T data[3];
    swizzle<T, 3, 1, 0x00> x, r;
    swizzle<T, 3, 1, 0x01> y, g;
    swizzle<T, 3, 1, 0x02> z, b;
    swizzle<T, 3, 2, 0x0000> xx, rr;
    swizzle<T, 3, 2, 0x0100> xy, rg;
    swizzle<T, 3, 2, 0x0200> xz, rb;
    swizzle<T, 3, 2, 0x0001> yx, gr;
    swizzle<T, 3, 2, 0x0101> yy, gg;
    swizzle<T, 3, 2, 0x0201> yz, gb;
    swizzle<T, 3, 2, 0x0002> zx, br;
    swizzle<T, 3, 2, 0x0102> zy, bg;
    swizzle<T, 3, 2, 0x0202> zz, bb;
    swizzle<T, 3, 3, 0x000000> xxx, rrr;
    swizzle<T, 3, 3, 0x010000> xxy, rrg;
    swizzle<T, 3, 3, 0x020000> xxz, rrb;
    swizzle<T, 3, 3, 0x000100> xyx, rgr;
    swizzle<T, 3, 3, 0x010100> xyy, rgg;
    swizzle<T, 3, 3, 0x020100> xyz, rgb;
    swizzle<T, 3, 3, 0x000200> xzx, rbr;
    swizzle<T, 3, 3, 0x010200> xzy, rbg;
    swizzle<T, 3, 3, 0x020200> xzz, rbb;
    swizzle<T, 3, 3, 0x000001> yxx, grr;
    swizzle<T, 3, 3, 0x010001> yxy, grg;
    swizzle<T, 3, 3, 0x020001> yxz, grb;
    swizzle<T, 3, 3, 0x000101> yyx, ggr;
    swizzle<T, 3, 3, 0x010101> yyy, ggg;
    swizzle<T, 3, 3, 0x020101> yyz, ggb;
    swizzle<T, 3, 3, 0x000201> yzx, gbr;
    swizzle<T, 3, 3, 0x010201> yzy, gbg;
    swizzle<T, 3, 3, 0x020201> yzz, gbb;
    swizzle<T, 3, 3, 0x000002> zxx, brr;
    swizzle<T, 3, 3, 0x010002> zxy, brg;
    swizzle<T, 3, 3, 0x020002> zxz, brb;
    swizzle<T, 3, 3, 0x000102> zyx, bgr;
    swizzle<T, 3, 3, 0x010102> zyy, bgg;
    swizzle<T, 3, 3, 0x020102> zyz, bgb;
    swizzle<T, 3, 3, 0x000202> zzx, bbr;
    swizzle<T, 3, 3, 0x010202> zzy, bbg;
    swizzle<T, 3, 3, 0x020202> zzz, bbb;
    swizzle<T, 3, 4, 0x00000000> xxxx, rrrr;
    swizzle<T, 3, 4, 0x01000000> xxxy, rrrg;
    swizzle<T, 3, 4, 0x02000000> xxxz, rrrb;
    swizzle<T, 3, 4, 0x00010000> xxyx, rrgr;
    swizzle<T, 3, 4, 0x01010000> xxyy, rrgg;
    swizzle<T, 3, 4, 0x02010000> xxyz, rrgb;
    swizzle<T, 3, 4, 0x00020000> xxzx, rrbr;
    swizzle<T, 3, 4, 0x01020000> xxzy, rrbg;
    swizzle<T, 3, 4, 0x02020000> xxzz, rrbb;
    swizzle<T, 3, 4, 0x00000100> xyxx, rgrr;
    swizzle<T, 3, 4, 0x01000100> xyxy, rgrg;
    swizzle<T, 3, 4, 0x02000100> xyxz, rgrb;
    swizzle<T, 3, 4, 0x00010100> xyyx, rggr;
    swizzle<T, 3, 4, 0x01010100> xyyy, rggg;
    swizzle<T, 3, 4, 0x02010100> xyyz, rggb;
    swizzle<T, 3, 4, 0x00020100> xyzx, rgbr;
    swizzle<T, 3, 4, 0x01020100> xyzy, rgbg;
    swizzle<T, 3, 4, 0x02020100> xyzz, rgbb;
    swizzle<T, 3, 4, 0x00000200> xzxx, rbrr;
    swizzle<T, 3, 4, 0x01000200> xzxy, rbrg;
    swizzle<T, 3, 4, 0x02000200> xzxz, rbrb;
    swizzle<T, 3, 4, 0x00010200> xzyx, rbgr;
    swizzle<T, 3, 4, 0x01010200> xzyy, rbgg;
    swizzle<T, 3, 4, 0x02010200> xzyz, rbgb;
    swizzle<T, 3, 4, 0x00020200> xzzx, rbbr;
    swizzle<T, 3, 4, 0x01020200> xzzy, rbbg;
    swizzle<T, 3, 4, 0x02020200> xzzz, rbbb;
    swizzle<T, 3, 4, 0x00000001> yxxx, grrr;
    swizzle<T, 3, 4, 0x01000001> yxxy, grrg;
    swizzle<T, 3, 4, 0x02000001> yxxz, grrb;
    swizzle<T, 3, 4, 0x00010001> yxyx, grgr;
    swizzle<T, 3, 4, 0x01010001> yxyy, grgg;
    swizzle<T, 3, 4, 0x02010001> yxyz, grgb;
    swizzle<T, 3, 4, 0x00020001> yxzx, grbr;
    swizzle<T, 3, 4, 0x01020001> yxzy, grbg;
    swizzle<T, 3, 4, 0x02020001> yxzz, grbb;
    swizzle<T, 3, 4, 0x00000101> yyxx, ggrr;
    swizzle<T, 3, 4, 0x01000101> yyxy, ggrg;
    swizzle<T, 3, 4, 0x02000101> yyxz, ggrb;
    swizzle<T, 3, 4, 0x00010101> yyyx, gggr;
    swizzle<T, 3, 4, 0x01010101> yyyy, gggg;
    swizzle<T, 3, 4, 0x02010101> yyyz, gggb;
    swizzle<T, 3, 4, 0x00020101> yyzx, ggbr;
    swizzle<T, 3, 4, 0x01020101> yyzy, ggbg;
    swizzle<T, 3, 4, 0x02020101> yyzz, ggbb;
    swizzle<T, 3, 4, 0x00000201> yzxx, gbrr;
    swizzle<T, 3, 4, 0x01000201> yzxy, gbrg;
    swizzle<T, 3, 4, 0x02000201> yzxz, gbrb;
    swizzle<T, 3, 4, 0x00010201> yzyx, gbgr;
    swizzle<T, 3, 4, 0x01010201> yzyy, gbgg;
    swizzle<T, 3, 4, 0x02010201> yzyz, gbgb;
    swizzle<T, 3, 4, 0x00020201> yzzx, gbbr;
    swizzle<T, 3, 4, 0x01020201> yzzy, gbbg;
    swizzle<T, 3, 4, 0x02020201> yzzz, gbbb;
    swizzle<T, 3, 4, 0x00000002> zxxx, brrr;
    swizzle<T, 3, 4, 0x01000002> zxxy, brrg;
    swizzle<T, 3, 4, 0x02000002> zxxz, brrb;
    swizzle<T, 3, 4, 0x00010002> zxyx, brgr;
    swizzle<T, 3, 4, 0x01010002> zxyy, brgg;
    swizzle<T, 3, 4, 0x02010002> zxyz, brgb;
    swizzle<T, 3, 4, 0x00020002> zxzx, brbr;
    swizzle<T, 3, 4, 0x01020002> zxzy, brbg;
    swizzle<T, 3, 4, 0x02020002> zxzz, brbb;
    swizzle<T, 3, 4, 0x00000102> zyxx, bgrr;
    swizzle<T, 3, 4, 0x01000102> zyxy, bgrg;
    swizzle<T, 3, 4, 0x02000102> zyxz, bgrb;
    swizzle<T, 3, 4, 0x00010102> zyyx, bggr;
    swizzle<T, 3, 4, 0x01010102> zyyy, bggg;
    swizzle<T, 3, 4, 0x02010102> zyyz, bggb;
    swizzle<T, 3, 4, 0x00020102> zyzx, bgbr;
    swizzle<T, 3, 4, 0x01020102> zyzy, bgbg;
    swizzle<T, 3, 4, 0x02020102> zyzz, bgbb;
    swizzle<T, 3, 4, 0x00000202> zzxx, bbrr;
    swizzle<T, 3, 4, 0x01000202> zzxy, bbrg;
    swizzle<T, 3, 4, 0x02000202> zzxz, bbrb;
    swizzle<T, 3, 4, 0x00010202> zzyx, bbgr;
    swizzle<T, 3, 4, 0x01010202> zzyy, bbgg;
    swizzle<T, 3, 4, 0x02010202> zzyz, bbgb;
    swizzle<T, 3, 4, 0x00020202> zzzx, bbbr;
    swizzle<T, 3, 4, 0x01020202> zzzy, bbbg;
    swizzle<T, 3, 4, 0x02020202> zzzz, bbbb;
  };
};
template <typename T> struct vec<T, 4> {
  constexpr vec() : data{T(), T(), T(), T()} {}
  constexpr vec(const T &x_, const T &y_, const T &z_, const T &w_)
      : data{x_, y_, z_, w_} {}
  constexpr explicit vec(const T &v_) : data{v_, v_, v_, v_} {}
  template <typename U, size_t N,
            typename std::enable_if<(N >= 4)>::type * = nullptr>
  constexpr explicit vec(const vec<U, N> &v)
      : data{static_cast<T>(v.data[0]), static_cast<T>(v.data[1]),
             static_cast<T>(v.data[2]), static_cast<T>(v.data[3])} {}

  constexpr const T &operator[](size_t i) const { return data[i]; }
  constexpr T &operator[](size_t i) { return data[i]; }

  union {
    T data[4];
    swizzle<T, 4, 1, 0x00> x, r;
    swizzle<T, 4, 1, 0x01> y, g;
    swizzle<T, 4, 1, 0x02> z, b;
    swizzle<T, 4, 1, 0x03> w, a;
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

template <typename T, typename U, size_t N, size_t M>
constexpr inline typename std::enable_if<N != M, bool>::type
operator==(const vec<T, N> &lhs, const vec<U, M> &rhs) {
  return false;
}
template <typename T, typename U, size_t N, size_t M>
constexpr inline typename std::enable_if<N == M, bool>::type
operator==(const vec<T, N> &lhs, const vec<U, M> &rhs) {
  for (size_t i = 0; i < N; ++i) {
    if (lhs.data[i] != rhs.data[i])
      return false;
  }
  return true;
}
template <typename T, typename U>
constexpr inline bool operator==(const vec<T, 1> &lhs, const vec<U, 1> &rhs) {
  return lhs.data[0] == rhs.data[0];
}
template <typename T, typename U>
constexpr inline bool operator==(const vec<T, 2> &lhs, const vec<U, 2> &rhs) {
  return lhs.data[0] == rhs.data[0] && lhs.data[1] == rhs.data[1];
}
template <typename T, typename U>
constexpr inline bool operator==(const vec<T, 3> &lhs, const vec<U, 3> &rhs) {
  return lhs.data[0] == rhs.data[0] && lhs.data[1] == rhs.data[1] &&
         lhs.data[2] == rhs.data[2];
}
template <typename T, typename U>
constexpr inline bool operator==(const vec<T, 4> &lhs, const vec<U, 4> &rhs) {
  return lhs.data[0] == rhs.data[0] && lhs.data[1] == rhs.data[1] &&
         lhs.data[2] == rhs.data[2] && lhs.data[3] == rhs.data[3];
}

} // namespace vml

#endif // VML_HPP_
