#ifndef CPP_UTIL_STRING_UTIL_H
#define CPP_UTIL_STRING_UTIL_H
#include <string>
#include <vector>

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

#endif // CPP_UTIL_STRING_UTIL_H
