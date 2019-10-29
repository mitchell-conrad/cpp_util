#ifndef CPP_UTIL_MUTEX_H
#define CPP_UTIL_MUTEX_H

#include <mutex>

namespace cpp_util {

template<typename T>
class mutex {
  T internal_val_;
  std::mutex internal_mutex_;

public:
  explicit mutex(T internal_val) : internal_val_(internal_val){};

  template<typename F>
  auto
  apply(F func) -> void
  {
    std::lock_guard<std::mutex> lock(internal_mutex_);
    func(internal_val_);
  };
  auto
  get() -> T
  {
    std::lock_guard<std::mutex> lock(internal_mutex_);
    return internal_val_;
  }
};
} // namespace cpp_util

#endif // CPP_UTIL_MUTEX_H
