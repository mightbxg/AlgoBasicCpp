#pragma once

#include <algorithm>
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

namespace details_quicksort { // quick sort
    inline void quickSort(std::vector<int>& vec, int l, int r)
    {
        if (l >= r)
            return;
        // partition
        int i = l, j = r;
        while (i < j) {
            while (i < j && vec[j] >= vec[l])
                --j;
            while (i < j && vec[i] <= vec[l])
                ++i;
            std::swap(vec[i], vec[j]);
        }
        std::swap(vec[i], vec[l]);
        // divide and conquer
        quickSort(vec, l, i - 1);
        quickSort(vec, i + 1, r);
    }

    void quickSortStd(std::vector<int>::iterator begin,
        std::vector<int>::iterator end)
    {
        if (end - begin < 2)
            return;
        // partition
        auto pivot = begin + (end - begin) / 2;
        std::nth_element(begin, pivot, end);
        // divide and conqure
        sort(begin, pivot);
        sort(pivot + 1, end);
    }
} // namespace details

/// time: O(n*logn)
///     [n] compares & swaps per recursion, [logn] recirsion depth
/// space: O(1)
/// un-stable
void quickSort(std::vector<int>& v)
{
    return details_quicksort::quickSort(v, 0, v.size() - 1);
}

void quickSortStd(std::vector<int>& v)
{
    return details_quicksort::quickSortStd(v.begin(), v.end());
}

namespace details_mergesort {
    void merge(std::vector<int>& vec, int low, int mid, int high)
    {
        std::vector<int> tmp(high - low);
        for (int i = low; i < high; ++i)
            tmp[i - low] = vec[i];
        int p1 = 0, p2 = mid - low, p = low;
        while (p1 < mid - low || p2 < high - low) {
            if (p1 >= mid - low)
                vec[p] = tmp[p2++];
            else if (p2 >= high - low)
                vec[p] = tmp[p1++];
            else if (tmp[p1] < tmp[p2])
                vec[p] = tmp[p1++];
            else
                vec[p] = tmp[p2++];
            ++p;
        }
    }

    void sort(std::vector<int>& vec, int low, int high)
    {
        if (high - low < 2)
            return;
        int mid = low + (high - low) / 2;
        sort(vec, low, mid);
        sort(vec, mid, high);
        merge(vec, low, mid, high);
    }
} // namespace details_mergesort

/// time: O(n*logn)
/// space: O(n)
/// stable
void mergeSort(std::vector<int>& v)
{
    return details_mergesort::sort(v, 0, v.size());
}

} // namespace abc::ref
