#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>

namespace linq {
namespace impl {

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class until_enumerator;
template<typename T, typename F>
class where_enumerator;
template<typename T>
class take_enumerator;

template<typename T>
class enumerator {
public:
  virtual T operator*() const = 0; // Получает текущий элемент.
  virtual enumerator& operator++() = 0;  // Переход к следующему элементу
  virtual explicit operator bool() const = 0;  // Возвращает true, если есть текущий элемент

  auto drop(int count) {
    return drop_enumerator<T>(*this, count);
  }

  template<typename U = T, typename F>
  auto select(F&& func) {
    return select_enumerator<U, T, F>(*this, std::forward<F>(func));
  }

  template<typename F>
  auto until(F&& func) {
    return until_enumerator<T, F>(*this, std::forward<F>(func));
  }

  auto until_eq(const T& value) {
      return until([value](const T& x) { return x == value; });
    }

  template<typename F>
  auto where(F&& func) {
    return where_enumerator<T, F>(*this, std::forward<F>(func));
  }

  auto where_neq(const T& value) {
    return where([value](const T& x) { return x != value; });
  }

  auto take(int count) {
        return take_enumerator<T>(*this, count);
    }


  std::vector<T> to_vector() {
    std::vector<T> result;
    while (*this) {
      result.push_back(**this);
      ++(*this);
    }
    return result;
  }

  template<typename Iter>
  void copy_to(Iter it) {
    while (*this) {
      *it++ = **this;
      ++(*this);
    }
  }
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
    range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

    T operator*() const override {
        return *begin_;
    }

    enumerator<T>& operator++() override {
        if (begin_ != end_) {
            ++begin_;
        }
        return *this;
    }

    explicit operator bool() const override {
        return begin_ != end_;
    }

private:
    Iter begin_, end_;
};

template<typename T>
class drop_enumerator : public enumerator<T> {
public:
  drop_enumerator(enumerator<T>& parent, int count) : parent_(parent), count_(count) {
    for (int i = 0; i < count_ && parent_; ++i) {
        ++parent_;
    }
  }

  T operator*() const override {
    return *parent_;
  }

  enumerator<T>& operator++() override {
    ++parent_;
    return *this;
  }

  explicit operator bool() const override {
    return static_cast<bool>(parent_);
  }

private:
  enumerator<T>& parent_;
  int count_;
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
  select_enumerator(enumerator<U>& parent, F&& func) : parent_(parent), func_(std::forward<F>(func)) {}

  T operator*() const override {
    return func_(*parent_);
  }

  enumerator<T>& operator++() override {
    ++parent_;
    return *this;
  }

  explicit operator bool() const override {
    return static_cast<bool>(parent_);
  }

private:
  enumerator<U>& parent_;
  F func_;
};

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
  until_enumerator(enumerator<T>& parent, F&& predicate) 
    : parent_(parent), predicate_(std::forward<F>(predicate)), done_(false) {
    check_done();
  }

  T operator*() const override {
    return *parent_;
  }

  enumerator<T>& operator++() override {
    ++parent_;
    check_done();
    return *this;
  }

  explicit operator bool() const override {
    return !done_ && static_cast<bool>(parent_);
  }

private:
  void check_done() {
    if (parent_ && predicate_(*parent_)) {
      done_ = true;
    }
  }

  enumerator<T>& parent_;
  F predicate_;
  bool done_;
};


template<typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
  where_enumerator(enumerator<T>& parent, F&& predicate) : parent_(parent), predicate_(std::forward<F>(predicate)) {
    while (parent_ && !predicate_(*parent_)) {
      ++parent_;
    }
  }

  T operator*() const override {
    return *parent_;
  }

  enumerator<T>& operator++() override {
    do {
      ++parent_;
    } while (parent_ && !predicate_(*parent_));
    return *this;
  }

  explicit operator bool() const override {
    return static_cast<bool>(parent_);
  }

private:
  enumerator<T>& parent_;
  F predicate_;
};

template<typename T>
class take_enumerator : public enumerator<T> {
public:
  take_enumerator(enumerator<T>& parent, int count) : parent_(parent), count_(count), taken_(0) {}

  T operator*() const override {
    return *parent_;
  }

  enumerator<T>& operator++() override {
    ++parent_;
    ++taken_;
    return *this;
  }

  explicit operator bool() const override {
    return taken_ < count_ && static_cast<bool>(parent_);
  }

private:
  enumerator<T>& parent_;
  int count_;
  int taken_;
};

} // namespace impl

template<typename T>
auto from(T begin, T end) {
  return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

} // namespace linq

#endif
