#pragma once

#include <vector>

namespace abc::ref {

/// time:O(n*n) space:O(1) nonstable
inline void bubbleSort(std::vector<int>& vec)
{
    for (std::size_t i = 0; i < vec.size() - 1; ++i) {
        for (std::size_t j = 0; j < vec.size() - 1 - i; ++j) {
            if (vec[j] > vec[j + 1])
                std::swap(vec[j], vec[j + 1]);
        }
    }
}

/// time:O(n*n) space:O(1) nonstable
inline void selectSort(std::vector<int>& vec)
{
    for (std::size_t i = 0; i < vec.size() - 1; ++i) {
        std::size_t min_id = i;
        for (std::size_t j = i; j < vec.size(); ++j) {
            if (vec[j] < vec[min_id])
                min_id = j;
        }
        std::swap(vec[i], vec[min_id]);
    }
}

} //namespace abc::ref
