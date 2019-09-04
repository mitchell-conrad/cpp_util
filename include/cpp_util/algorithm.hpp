#pragma once
#include <functional>

// all_of, any_of utility functions
// Inspired by:
// (Björn Fahller: Modern techniques for keeping your code DRY) [https://youtu.be/tdxQm1DwD_A]

namespace util {
// TODO: use cpp20 feature flags to enable/disable parameter pack perfect forwarding
namespace detail {
    constexpr auto tuple = [](auto... ts) {
        return [=](const auto& func) noexcept(noexcept(func(ts...))) -> decltype(func(ts...)) {
            return func(ts...);
        };
    };

    constexpr auto or_elements = [](auto&& func) {
        return [func = std::forward<decltype(func)>(func)](auto... elements) noexcept(
                   noexcept((func(elements) || ...))) -> decltype((func(elements) || ...)) {
            return (func(elements) || ...);
        };
    };

    constexpr auto and_elements = [](auto&& func) {
        return [func = std::forward<decltype(func)>(func)](auto... elements) noexcept(
                   noexcept((func(elements) && ...))) -> decltype((func(elements) && ...)) {
            return (func(elements) && ...);
        };
    };
    constexpr auto bind_rh = [](auto func, auto rh) {
        return [=](auto lh) { return func(lh, rh); };
    };
} // namespace detail

constexpr auto less_than = [](auto rh) { return detail::bind_rh(std::less{}, rh); };
constexpr auto greater_than = [](auto rh) { return detail::bind_rh(std::greater{}, rh); };
constexpr auto equal_to = [](auto rh) { return detail::bind_rh(std::equal_to{}, rh); };
constexpr auto not_equal_to = [](auto rh) { return detail::bind_rh(std::not_equal_to{}, rh); };

namespace detail {

    template<typename Func, typename Tuple>
    class op_t {
        Tuple tup_;
        Func func_;
        template<typename F>
        constexpr auto apply(F&& f) const noexcept(noexcept(tup_(func_(std::forward<F>(f)))))
        {
            return tup_(func_(std::forward<F>(f)));
        }

    public:
        op_t(Func f, Tuple t) : tup_(std::move(t)), func_(std::move(f)) {}

        // TODO: Add other comparison operators
        template<typename T>
        constexpr auto operator==(const T& t) const
        {
            return apply(equal_to(t));
        }

        template<typename T>
        friend constexpr auto operator==(const T& lh, const op_t& rh)
        {
            return rh == lh;
        }

        template<typename T>
        constexpr auto operator>(const T& t) const
        {
            return apply(greater_than(t));
        }
        template<typename T>
        friend constexpr auto operator>(const T& lh, const op_t& rh)
        {
            return rh < lh;
        }

        template<typename T>
        constexpr auto operator<(const T& t) const
        {
            return apply(less_than(t));
        }
        template<typename T>
        friend constexpr auto operator<(const T& lh, const op_t& rh)
        {
            return rh > lh;
        }
    };

} // namespace detail

constexpr auto all_of = [](auto... ts) {
    return detail::op_t(detail::and_elements, detail::tuple(std::forward<decltype(ts)>(ts)...));
};
constexpr auto any_of = [](auto... ts) {
    return detail::op_t(detail::or_elements, detail::tuple(std::forward<decltype(ts)>(ts)...));
};

} // namespace util