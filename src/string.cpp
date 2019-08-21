#include <cpp_util/string.hpp>

namespace util {

auto intercalate(std::vector<std::string> in, const std::string& separator) -> std::string
{
    auto it = std::begin(in);
    std::string out = *it;

    it = std::next(it);
    while(it != std::end(in)) {
        out += separator;
        out += *it;
        it = std::next(it);
    }
    return out;
}
} // namespace util
