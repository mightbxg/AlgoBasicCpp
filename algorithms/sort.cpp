#include "sort.h"

namespace abc::ref {

void bubbleSort(std::vector<int>& vec)
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

void selectSort(std::vector<int>& vec)
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

void insertSort(std::vector<int>& vec)
{
    for (std::size_t i = 1; i < vec.size(); ++i) {
        for (std::size_t j = i; j > 0; --j) {
            if (vec[j] > vec[j - 1])
                break;
            std::swap(vec[j - 1], vec[j]);
        }
    }
}

void shellSort(std::vector<int>& vec)
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

static void quickSort(std::vector<int>& vec, int l, int r)
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

void quickSort(std::vector<int>& v)
{
    return quickSort(v, 0, v.size() - 1);
}

static void quickSortStd(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    if (end - begin < 2)
        return;
    // partition
    auto pivot = begin + (end - begin) / 2;
    std::nth_element(begin, pivot, end);
    // divide and conqure
    quickSortStd(begin, pivot);
    quickSortStd(pivot + 1, end);
}

void quickSortStd(std::vector<int>& v)
{
    return quickSortStd(v.begin(), v.end());
}

void mergeSort(std::vector<int>& vec, int low, int high)
{
    if (high - low < 2)
        return;
    int mid = low + (high - low) / 2;
    mergeSort(vec, low, mid);
    mergeSort(vec, mid, high);
    // merge
    std::vector<int> tmp(high - low);
    std::copy(vec.begin() + low, vec.begin() + high, tmp.begin());
    const int low_size = mid - low, all_size = high - low;
    int p1 = 0, p2 = low_size, p = low;
    while (p1 < low_size && p2 < all_size)
        vec[p++] = tmp[p1] <= tmp[p2] ? tmp[p1++] : tmp[p2++];
    while (p1 < low_size)
        vec[p++] = tmp[p1++];
    while (p2 < all_size)
        vec[p++] = tmp[p2++];
}

void mergeSort(std::vector<int>& v)
{
    return mergeSort(v, 0, v.size());
}

} // namespace abc::ref
