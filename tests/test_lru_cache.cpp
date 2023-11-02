#include "algorithms/lru_cache.h"
#include <gtest/gtest.h>

static inline double Key2Val(int key)
{
    return key + key * 0.1;
}

TEST(lru_cache, insert)
{
    const int capacity = 5;
    abc::ref::LruCache<int, double> cache(capacity);
    ASSERT_EQ(cache.size(), 0);
    ASSERT_EQ(cache.capacity(), capacity);

    for (int i = 0; i < capacity; ++i) {
        cache.insert(i, Key2Val(i));
        ASSERT_EQ(cache.size(), i + 1);
        ASSERT_EQ(cache.capacity(), capacity);
        int j = 0;
        for (const auto& kv : cache.data()) {
            ASSERT_EQ(kv.first, j);
            ASSERT_DOUBLE_EQ(kv.second, Key2Val(j));
            ++j;
        }
    }

    for (int i = capacity; i < capacity * 2; ++i) {
        cache.insert(i, Key2Val(i));
        ASSERT_EQ(cache.size(), capacity);
        ASSERT_EQ(cache.capacity(), capacity);
        int j = i - static_cast<int>(capacity) + 1;
        for (const auto& kv : cache.data()) {
            ASSERT_EQ(kv.first, j);
            ASSERT_DOUBLE_EQ(kv.second, Key2Val(j));
            ++j;
        }
    }
}

TEST(lru_cache, get)
{
    const int capacity = 5;
    abc::ref::LruCache<int, double> cache(capacity);
    for (int i = 0; i < capacity; ++i) {
        cache.insert(i, Key2Val(i));
    }
    ASSERT_EQ(cache.get(-1), cache.data().end());
    ASSERT_EQ(cache.get(5), cache.data().end());

    int key = 2;
    auto node = cache.get(key);
    ASSERT_EQ(node->first, key);
    ASSERT_DOUBLE_EQ(node->second, Key2Val(key));
    auto last_node = std::prev(cache.data().end());
    ASSERT_EQ(node, last_node);
}
