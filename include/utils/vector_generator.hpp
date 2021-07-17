#pragma once

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

namespace abc {

template <typename Scalar = int>
class VectorGenerator {
public:
    static std::vector<Scalar> genSortedVec(std::size_t size = 10)
    {
        std::vector<Scalar> ret(size);
        std::iota(ret.begin(), ret.end(), 0);
        return ret;
    }

    /// shuffle the given vector randomly
    /// if seed < 0, it will be chosen randomly
    static void randomShuffle(std::vector<Scalar>& vec, int seed = -1)
    {
        std::random_device rd;
        unsigned s = seed < 0 ? rd() : seed;
        std::mt19937 g(s);
        std::shuffle(vec.begin(), vec.end(), g);
    }
};

} //namespace abc
