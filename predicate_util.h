#include <functional>
#include <numeric>
#include <vector>

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
auto combine_or(unary_predicate<T> a, unary_predicate<T> b) -> unary_predicate<T> {
    return [a,b](T in) -> bool{
                return a(in) || b(in);
                    
    };

}

template<class T>
auto combine_and(unary_predicate<T> a, unary_predicate<T> b) -> unary_predicate<T> {
    return [a,b](T in) -> bool{
                return a(in) && b(in);
                    
    };

}

template<class T>
auto disjunction(std::vector<unary_predicate<T>> preds) -> unary_predicate<T> {
        return std::accumulate(preds.begin(), preds.end(),
                            false_id<T>(),
                                        combine_or<T>);

}

template<class T>
auto conjunction(std::vector<unary_predicate<T>> preds) -> unary_predicate<T> {
        return std::accumulate(preds.begin(), preds.end(),
                            true_id<T>(),
                                        combine_and<T>);

}
