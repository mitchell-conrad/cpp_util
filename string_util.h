#ifndef CPP_UTIL_STRING_UTIL_H
#define CPP_UTIL_STRING_UTIL_H
#include <string>
#include <vector>

namespace util {

auto intercalate(std::vector<std::string> in, std::string seperator) {
    auto it = std::begin(in);
    std::string out = *it;

    it = std::next(it);
    while(it != std::end(in)) {
        out += seperator;
        out += *it;
        it = std::next(it);
    }
    return out;
}
} // namespace util
#endif // CPP_UTIL_STRING_UTIL_H
