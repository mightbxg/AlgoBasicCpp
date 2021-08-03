#pragma once

#include <vector>

namespace abc::ref {

/// time: O(n*n)
/// space: O(1)
/// stable
inline void bubbleSort(std::vector<int>& vec)
{
    if (vec.empty())
        return;
    for (std::size_t i = 0; i < vec.size() - 1; ++i) {
        for (std::size_t j = 0; j < vec.size() - 1 - i; ++j) {
            if (vec[j] > vec[j + 1])
                std::swap(vec[j], vec[j + 1]);
        }
    }
}

/// time: O(n*n)
/// space: O(1)
/// can-be-stable
inline void selectSort(std::vector<int>& vec)
{
    if (vec.empty())
        return;
    for (std::size_t i = 0; i < vec.size() - 1; ++i) {
        std::size_t min_id = i;
        for (std::size_t j = i; j < vec.size(); ++j) {
            if (vec[j] < vec[min_id])
                min_id = j;
        }
        std::swap(vec[i], vec[min_id]);
    }
}

/// time: O(n*n) [best O(n)]
/// space: O(1)
/// stable
inline void insertSort(std::vector<int>& vec)
{
    for (std::size_t i = 1; i < vec.size(); ++i) {
        for (std::size_t j = i; j > 0; --j) {
            if (vec[j] > vec[j - 1])
                break;
            std::swap(vec[j - 1], vec[j]);
        }
    }
}

/// time: O(n*logn)
/// space: O(1)
/// un-stable
inline void shellSort(std::vector<int>& vec)
{
    std::size_t gap = vec.size();
    while ((gap = (gap >> 1)) > 0) {
        for (std::size_t i = gap; i < vec.size(); ++i) {
            for (std::size_t j = i; j >= gap; j -= gap) {
                if (vec[j] > vec[j - gap])
                    break;
                std::swap(vec[j], vec[j - gap]);
            }
        }
    }
}

} //namespace abc::ref
