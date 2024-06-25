#include <cstddef>
#include <iterator>
#include <stdexcept>

template <class T, std::size_t N> struct array {
public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef pointer iterator;
  typedef const_pointer const_iterator;
  typedef std::reverse_iterator<pointer> reverse_iterator;
  typedef std::reverse_iterator<const_pointer> const_reverse_iterator;

  array() = default;
  ~array() = default;
  array<T, N> &operator=(const array<T, N> &array) = default;

  constexpr iterator end() noexcept { return _data + N; }

  constexpr const_iterator end() const noexcept { return end(); }

  constexpr const_iterator cend() noexcept { return end(); }

  constexpr iterator begin() noexcept {
    if (N > 0) {
      return data;
    }
    return end();
  }

  constexpr const_iterator begin() const noexcept { return begin(); }

  constexpr const_iterator cbegin() const noexcept { return begin(); }

  constexpr reverse_iterator rend() noexcept { return _data - 1; }

  constexpr const_reverse_iterator rend() const noexcept { return rend(); }

  constexpr const_reverse_iterator crend() const noexcept { return rend(); }

  constexpr reverse_iterator rbegin() noexcept {
    if (N > 0) {
      return data;
    }
    return rend();
  }

  constexpr const_reverse_iterator rbegin() const noexcept { return rbegin(); }

  constexpr const_reverse_iterator crbegin() const noexcept { return rbegin(); }

  [[nodiscard]] constexpr bool empty() const noexcept {
    return begin() == end();
  }

  constexpr size_type size() const noexcept {
    return std::distance(begin(), end());
  }

  constexpr size_type max_size() const noexcept {
    return std::distance(begin(), end());
  }

  constexpr reference at(size_type pos) {
    if (pos >= size()) {
      throw std::out_of_range("index out of bounds");
    }
    return _data[pos];
  };

  constexpr const_reference at(size_type pos) const { return at(pos); };

  constexpr reference operator[](size_type pos) { return _data[pos]; }

  constexpr const_reference operator[](size_type pos) const {
    return this[pos];
  }

  constexpr reference front() { return _data[0]; }

  constexpr const_reference front() const { return front(); }

  constexpr reference back() { return _data[N - 1]; }

  constexpr const_reference back() const { return back(); }

  constexpr pointer data() noexcept { return data; }

  constexpr const_pointer data() const noexcept { return data(); }

  constexpr void fill(const_reference value) {
    for (auto &element : _data) {
      element = value;
    }
  }

  constexpr void swap(array &other) noexcept(std::is_nothrow_swappable_v<T>) {
    for (size_t i = 0; i < N; i++) {
      value_type temp = other[i];
      other[i] = this[i];
      this[i] = temp;
    }
  }

private:
  value_type _data[N];
};

template <class T, std::size_t N>
constexpr bool operator==(const std::array<T, N> &lhs,
                          const std::array<T, N> &rhs) {
  for (size_t i = 0; i < N; i++) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

template <class T, std::size_t N>
constexpr bool operator!=(const std::array<T, N> &lhs,
                          const std::array<T, N> &rhs) {
  return !(lhs == rhs);
}

template <class T, std::size_t N>
constexpr bool operator<(const std::array<T, N> &lhs,
                         const std::array<T, N> &rhs) {
  for (size_t i = 0; i < N; i++) {
    if (lhs[i] >= rhs[i]) {
      return false;
    }
  }
  return true;
}

template <class T, std::size_t N>
constexpr bool operator<=(const std::array<T, N> &lhs,
                          const std::array<T, N> &rhs) {
  return lhs < rhs || lhs == rhs;
}

template <class T, std::size_t N>
constexpr bool operator>(const std::array<T, N> &lhs,
                         const std::array<T, N> &rhs) {
  return !(lhs <= rhs);
}

template <class T, std::size_t N>
constexpr bool operator>=(const std::array<T, N> &lhs,
                          const std::array<T, N> &rhs) {
  return lhs > rhs || lhs == rhs;
}
