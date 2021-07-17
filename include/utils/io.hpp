#pragma once

#include <array>
#include <iostream>
#include <vector>

namespace std {

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (const auto& v : vec)
        os << v << " ";
    return os;
}

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr)
{
    for (const auto& v : arr)
        os << v << " ";
    return os;
}

} //namespace std
