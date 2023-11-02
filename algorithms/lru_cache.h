#pragma once

#include <list>
#include <unordered_map>

namespace abc::ref {

template <typename Key, typename Value>
class LruCache {
public:
    using Cache = std::list<std::pair<Key, Value>>;
    using Node = typename Cache::iterator;
    using ConstNode = typename Cache::const_iterator;

    explicit LruCache(size_t capacity)
        : capacity_(capacity)
    {
        map_.reserve(capacity + 1);
    }

    void set_capacity(size_t n)
    {
        capacity_ = n;
        fit_capacity();
    }

    const auto& data() const { return cache_; }

    [[nodiscard]] auto size() const { return cache_.size(); }
    [[nodiscard]] auto capacity() const { return capacity_; }

    [[nodiscard]] bool contains(const Key& key) const
    {
        return map_.find(key) != map_.end();
    }

    /// @brief Insert KV as the last used one.
    /// @return true if insertion happened.
    bool insert(const Key& key, const Value& value)
    {
        if (get(key) != cache_.end())
            return false;
        auto node = cache_.emplace(cache_.end(), key, value);
        map_.emplace(key, node);
        fit_capacity();
        return true;
    }

    ConstNode get(const Key& key)
    {
        auto iter = map_.find(key);
        if (iter == map_.end())
            return cache_.cend();
        cache_.splice(cache_.end(), cache_, iter->second);
        return iter->second;
    }

private:
    void fit_capacity()
    {
        while (cache_.size() > capacity_) {
            auto& node = cache_.front();
            map_.erase(node.first);
            cache_.pop_front();
        }
    }

private:
    using Map = std::unordered_map<Key, Node>;
    size_t capacity_ { 10 };
    Cache cache_;
    Map map_;
};

} // namespace abc::ref
