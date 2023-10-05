#pragma once

#include <algorithm>
#include <vector>

namespace abc::ref {

/// time: O(n*n)
/// space: O(1)
/// stable
void bubbleSort(std::vector<int>& vec);

/// time: O(n*n)
/// space: O(1)
/// can-be-stable
void selectSort(std::vector<int>& vec);

/// time: O(n*n) [best O(n)]
/// space: O(1)
/// stable
void insertSort(std::vector<int>& vec);

/// time: O(n*logn)
/// space: O(1)
/// un-stable
void shellSort(std::vector<int>& vec);

/// time: O(n*logn)
///     [n] compares & swaps per recursion, [logn] recursion depth
/// space: O(1)
/// un-stable
void quickSort(std::vector<int>& v);

/// time: O(n*n)
///     [n] nth_element, [logn] recursion depth
void quickSortStd(std::vector<int>& v);

/// time: O(n*logn)
/// space: O(n)
/// stable
void mergeSort(std::vector<int>& v);

} // namespace abc::ref
