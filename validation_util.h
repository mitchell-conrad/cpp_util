#include <variant>
#include <iostream>
#include <utility>

template<class T>
class Invalid;

template<typename T>
class Valid {

    template<typename U>
    class ConstructorKey {
        friend class Invalid<U>;

        private:
        ConstructorKey(){};
        ConstructorKey(const ConstructorKey&) = default;
    };

    public:
        explicit Valid(T value, ConstructorKey<T>) : value_(std::move(value)) {};
        auto get() -> T {
            return value_;
        };
    private:
        T value_;
};

template<class T>
class Invalid {

    public:
        using validation_predicate_t = std::function<bool(T)>;
        Invalid(T value, const validation_predicate_t& validation_function) : 
            value_(std::move(value)),
            pred_(validation_function) {};

        auto validate() -> Valid<T> {
            if(pred_(value_))
                return Valid<T>(value_, {});

            throw std::invalid_argument("invalid");
        };

    private:
        T value_;
        validation_predicate_t pred_;

};

auto main() -> int {
    Invalid<int> invalid(1001, [](int val){
            return val > 1;
            }
    );

    Invalid<int> bad(-1, [](int val){
            return val > 1;
            }
    );

    using namespace std::placeholders;

    std::cout << invalid.validate().get() << std::endl;
//    std::cout << bad.validate().get() << std::endl;

    return invalid.validate().get();
}

