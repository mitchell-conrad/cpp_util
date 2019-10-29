#ifndef CPP_UTIL_REGISTRY_HPP
#define CPP_UTIL_REGISTRY_HPP

#include <optional>
#include <vector>

namespace cpp_util {

template<class T>
class registry {
  std::vector<std::pair<size_t, std::optional<T>>> map_;
  size_t size_ = 0;
  size_t id_ = 0;

public:
  [[nodiscard]] auto
  append(T element) -> size_t
  {
    map_.emplace_back(id_, std::move(element));
    ++size_;
    return id_++;
  }

  [[nodiscard]] auto
  get(size_t id) const -> const T&
  {
    using namespace std;
    auto p = lower_bound(begin(map_), end(map_), id,
                         [](const auto& a, const auto& b) { return a.first < b; });
    if(p == end(map_) || p->first != id || !p->second) {
      throw out_of_range("No value found with id");
    }
    return *(p->second);
  }

  auto
  erase(size_t id) -> void
  {
    using namespace std;

    // Find first slot not less than the asked for id
    auto p = lower_bound(begin(map_), end(map_), id,
                         [](const auto& a, const auto& b) { return a.first < b; });

    // Break early if our id isn't found
    if(p == end(map_) || p->first != id) {
      return;
    }

    // Erase our value at id
    p->second.reset();
    --size_;

    // If the number of valid elements we currently hold is less than half
    //   the current size of our map, erase(remove) idiom away our empty elements
    if(size_ < (map_.size() / 2)) {
      map_.erase(remove_if(begin(map_), end(map_),
                           [](const auto& element) { return !(element.second); }),
                 end(map_));
    }
  }

  template<class F>
  auto
  for_each(F f) const -> void
  {
    for(const auto& [id, element] : map_) {
      if(element) {
        f(*element);
      }
    }
  }
};
} // namespace cpp_util
#endif // CPP_UTIL_REGISTRY_HPP
