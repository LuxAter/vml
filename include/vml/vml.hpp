#ifndef VML_HPP_
#define VML_HPP_

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>

namespace vml {
template <typename T> struct matrix {
public:
  struct row_t {
    T *data;
    const size_t rows, cols;

    constexpr inline T &operator[](size_t i) { return *(data + i); }
    constexpr inline const T &operator[](size_t i) const { return *(data + i); }
  };
  struct column_t {
    T *data;
    const size_t rows, ccols;

    constexpr inline T &operator[](size_t i) { return *(data + i * rows); }
    constexpr inline const T &operator[](size_t i) const {
      return *(data + i * rows);
    }
  };

  constexpr inline matrix(size_t d)
      : data(static_cast<T *>(std::malloc(sizeof(T) * d * d))), rows(d),
        cols(d) {
    std::fill(data, data + rows * cols, T());
  }
  constexpr inline matrix(size_t r, size_t c)
      : data(static_cast<T *>(std::malloc(sizeof(T) * r * c))), rows(r),
        cols(c) {
    std::fill(data, data + rows * cols, T());
  }
  template <typename... Args>
  constexpr inline matrix(size_t r, size_t c, const Args &... args)
      : data(static_cast<T *>(std::malloc(sizeof(T) * sizeof...(Args)))),
        rows(r), cols(c) {
    assert(sizeof...(Args) == r * c);
    __construct<0>(args...);
  }
  inline ~matrix() { free(data); }

  constexpr inline row_t row(size_t r) {
    return row_t{data + r * cols, rows, cols};
  }
  constexpr inline column_t column(size_t c) {
    return column_t{data + c, rows, cols};
  }

#ifdef VML_COLUMN_MAJOR
  constexpr inline column_t operator[](size_t c) {
    return column_t{data + c, rows, cols};
  }
  constexpr inline const column_t operator[](size_t c) const {
    return column_t{data + c, rows, cols};
  }
#else
  constexpr inline row_t operator[](size_t r) {
    return row_t{data + r * cols, rows, cols};
  }
  constexpr inline const row_t operator[](size_t r) const {
    return row_t{data + r * cols, rows, cols};
  }
#endif

protected:
  T *data;
  size_t rows, cols;

private:
  template <size_t I> void __construct(const T &v) { data[I] = v; }
  template <size_t I, typename... Args>
  void __construct(const T &v, const Args &... args) {
    data[I] = v;
    __construct<I + 1>(args...);
  }
};
} // namespace vml

#endif // VML_HPP_
