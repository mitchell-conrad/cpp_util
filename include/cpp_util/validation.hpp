#pragma once

#include "predicate.hpp"
#include <functional>
#include <memory>

namespace util {

template<auto V, class T>
class validator;

/// valid wrapper with private only constructors
/// can only be constructed through validator.validate()
/// \tparam T type of contained data
template<auto V, typename T>
class valid {
  template<auto W, typename U>
  class constructor_key {
    friend class validator<W, U>;

  private:
    constructor_key() = default;
  };

public:
  /// @private
  /// \param value
  explicit valid(T value, constructor_key<V, T>) : value_(std::move(value)){};

  /// dereference operator, used to extract value of contained valid T
  /// \return an already validated T
  [[nodiscard]] auto operator*() -> T& { return value_; };

private:
  T value_;
};

/// Data validator
/// \tparam T type of data to be validated
template<auto V, class T>
class validator {
public:
  /// validator constructor
  /// \param validation_function unary predicate to validate values against
  explicit validator(const util::unary_predicate<T>& validation_function) :
    pred_(validation_function){};

  /// validate
  /// \param in value of type T to validate against validator
  /// \return valid wrapped T
  [[nodiscard]] auto validate(const T& in) -> valid<V, T>
  {
    if(pred_(in)) {
      return valid<V, T>(std::move(in), {});
    }
    throw std::invalid_argument("Validation predicate failed.");
  };

private:
  unary_predicate<T> pred_;
};

} // namespace util
