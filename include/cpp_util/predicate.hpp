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
auto pred_or(unary_predicate<T> a, unary_predicate<T> b) -> unary_predicate<T>
{
    return [a, b](T in) -> bool { return a(in) || b(in); };
}

template<class T>
auto pred_and(unary_predicate<T> a, unary_predicate<T> b) -> unary_predicate<T>
{
    return [a, b](T in) -> bool { return a(in) && b(in); };
}

template<class T>
auto disjunction(std::vector<unary_predicate<T>> predicates) -> unary_predicate<T>
{
    return std::accumulate(predicates.begin(), predicates.end(), false_id<T>(), pred_or<T>);
}

template<class T>
auto conjunction(std::vector<unary_predicate<T>> predicates) -> unary_predicate<T>
{
    return std::accumulate(predicates.begin(), predicates.end(), true_id<T>(), pred_and<T>);
}
} // namespace util