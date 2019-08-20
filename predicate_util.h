#ifndef CPP_UTIL_PREDICATE_UTIL_H
#define CPP_UTIL_PREDICATE_UTIL_H

#include <functional>
#include <numeric>
#include <vector>

namespace util {

template<class T>
using unary_predicate = std::function<bool(T)>;

template<class T>
auto false_id() -> unary_predicate<T>{
    return [](T in){
        return false;
    };
}

template<class T>
auto true_id() -> unary_predicate<T> {
    return [](T in){
        return true;
    };
}

template<class T>
auto pred_or(unary_predicate<T> a, unary_predicate<T> b) -> unary_predicate<T> {
    return [a,b](T in) -> bool{
        return a(in) || b(in);
    };
}

template<class T>
auto pred_and(unary_predicate<T> a, unary_predicate<T> b) -> unary_predicate<T> {
    return [a,b](T in) -> bool{
        return a(in) && b(in);
    };
}

template<class T>
auto pred_or(std::vector<unary_predicate<T>> preds) -> unary_predicate<T> {
        return std::accumulate(preds.begin(),
                                preds.end(),
                                true_id<T>(),
                                pred_or<T>);
}

template<class T>
auto pred_and(std::vector<unary_predicate<T>> preds) -> unary_predicate<T> {
        return std::accumulate(preds.begin(),
                                preds.end(),
                                false_id<T>(),
                                pred_or<T>);
}
} // namespace util
#endif // CPP_UTIL_PREDICATE_UTIL_H
