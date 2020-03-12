#pragma once
#ifndef VML_HPP_
#define VML_HPP_

#include <cstdlib>
#include <type_traits>
#include <utility>

namespace vml {
template <typename T, size_t N> struct vec;

namespace detail {
struct nothing {};
template <typename T, size_t N> struct vec_base;
template <typename T> constexpr auto decay(T &&t) -> decltype(t.decay()) {
  return t.decay();
}
template <typename T>
constexpr typename std::enable_if<
    std::is_arithmetic<typename std::remove_reference<T>::type>::value, T>::type
decay(T &&t) {
  return t;
}

template <typename T, size_t N, size_t... indices> struct swizzle {
  T data[N];
  constexpr inline vec<T, sizeof...(indices)> decay() const {
    vec<T, sizeof...(indices)> ret;
    assign_across<0>(ret, indices...);
    return ret;
  }
  constexpr inline operator vec<T, sizeof...(indices)>() { return decay(); }
  constexpr inline operator vec<T, sizeof...(indices)>() const {
    return decay();
  }
  swizzle &operator=(const vec<T, sizeof...(indices)> &v) {
    assign_across<0>(v, indices...);
  }

private:
  template <size_t I>
  constexpr inline void assign_across(vec<T, sizeof...(indices)> &v,
                                      size_t i) const {
    v[I] = data[i];
  }
  template <size_t I, typename... SwizzleIndicies>
  constexpr inline void assign_across(vec<T, sizeof...(indices)> &v, size_t i,
                                      SwizzleIndicies... swizz) const {
    v[I] = data[i];
    assign_across<I + 1>(v, swizz...);
  }
  template <size_t I>
  constexpr inline void assign_across(const vec<T, sizeof...(indices)> &v,
                                      size_t i) {
    data[i] = v[I];
  }
  template <size_t I, typename... SwizzleIndicies>
  constexpr inline void assign_across(const vec<T, sizeof...(indices)> &v,
                                      size_t i,
                                      SwizzleIndicies... swizz) const {
    data[i] = v[I];
    assign_across<I + 1>(v, swizz...);
  }
};

template <typename T, size_t N> struct vec_base {
  union {
    T data[N];
  };
};
template <typename T> struct vec_base<T, 1> { T data[1]; };
template <typename T> struct vec_base<T, 2> {
  union {
    T data[2];
    swizzle<T, 2, 0> x, r, s;
    swizzle<T, 2, 1> y, g, t;
    swizzle<T, 2, 0, 0> xx, rr, ss;
    swizzle<T, 2, 0, 1> xy, rg, st;
    swizzle<T, 2, 1, 0> yx, gr, ts;
    swizzle<T, 2, 1, 1> yy, gg, tt;
  };
};
template <typename T> struct vec_base<T, 3> { T data[3]; };

} // namespace detail

template <typename T, size_t N> struct vec : public detail::vec_base<T, N> {

  using detail::vec_base<T, N>::data;

  constexpr inline vec() {
    for (size_t i = 0; i < N; ++i)
      data[i] = T();
  }
  constexpr explicit inline vec(T &v) {
    for (size_t i = 0; i < N; ++i)
      data[i] = v;
  }
  template <typename... Args> constexpr inline vec(const Args &&... args) {
    __construct<0>(detail::decay(args)...);
  }

  T &operator[](size_t i) { return data[i]; }
  const T &operator[](size_t i) const { return data[i]; }

  constexpr inline typename std::conditional<N == 1, T, vec<T, N>>::type
  decay() const {
    return static_cast<
        const typename std::conditional<N == 1, T, vec<T, N>>::type &>(*this);
  }

  operator typename std::conditional<N == 1, T, detail::nothing>::type() const {
    return data[0];
  }

private:
  template <size_t I> constexpr void __construct(const T &v) { data[I] = v; }
  template <size_t I, size_t M> constexpr void __construct(const vec<T, M> &v) {
    for (std::size_t i = 0; i < M; ++i)
      data[I + i] = v;
  }
  template <size_t I, typename... Args>
  constexpr void __construct(const T &v, const Args &... args) {
    data[I] = v;
    __construct<I + 1>(args...);
  }
  template <size_t I, size_t M, typename... Args>
  constexpr void __construct(const vec<T, M> &v, const Args &... args) {
    for (std::size_t i = 0; i < M; ++i)
      data[I + i] = v;
    __construct<I + M>(args...);
  }
};
} // namespace vml

#endif // VML_HPP_
