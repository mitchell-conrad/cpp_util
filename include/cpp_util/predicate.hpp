#pragma once
#include <functional>
#include <numeric>
#include <vector>

namespace util {

template<class T>
using unary_predicate = std::function<bool(T)>;

template<class T>
constexpr auto false_id() -> unary_predicate<T>
{
  return [](T in) -> bool { return false; };
}

template<class T>
constexpr auto true_id() -> unary_predicate<T>
{
  return [](T in) -> bool { return true; };
}

template<class T>
auto pred_either(unary_predicate<T> a, unary_predicate<T> b) -> unary_predicate<T>
{
  return [a, b](T in) -> bool { return a(in) || b(in); };
}

template<class T>
auto pred_both(unary_predicate<T> a, unary_predicate<T> b) -> unary_predicate<T>
{
  return [a, b](T in) -> bool { return a(in) && b(in); };
}

template<class T>
auto pred_all(std::vector<unary_predicate<T>> predicates) -> unary_predicate<T>
{
  return std::accumulate(predicates.begin(), predicates.end(), true_id<T>(), pred_both<T>);
}

template<class T>
auto pred_any(std::vector<unary_predicate<T>> predicates) -> unary_predicate<T>
{
  return std::accumulate(predicates.begin(), predicates.end(), false_id<T>(), pred_either<T>);
}
} // namespace util