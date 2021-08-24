#include "sort.hpp"
#include "utils/io.hpp"
#include "utils/vector_generator.hpp"

using namespace std;
using namespace abc;

namespace {

using SortFunc = void(std::vector<int>&);
using VecGen = VectorGenerator<int>;
static const auto vec_ref = VecGen::genSortedVec(10);

bool testSortOnce(SortFunc sort, int shuffle_seed = -1);
void testSort(SortFunc sort);

#define TEST_SORT(func)                                  \
    {                                                    \
        std::cout << "[\33[36m" << #func << "\33[0m]: "; \
        testSort(func);                                  \
    }

void mySort(vector<int>& vec)
{
    // your sort algorithm code here
    (void)vec;
}

} //namespace

int main()
{
    TEST_SORT(mySort);
    TEST_SORT(ref::bubbleSort);
    TEST_SORT(ref::selectSort);
    TEST_SORT(ref::insertSort);
    TEST_SORT(ref::shellSort);
    TEST_SORT(ref::quickSort);
    TEST_SORT(ref::quickSortStd);
}

namespace {

bool testSortEmpty(SortFunc sort)
{
    vector<int> data = {};
    sort(data);
    if (!data.empty()) {
        std::cout << "\33[31m";
        std::cout << "test failed with empty data\n";
        std::cout << "\33[0m";
        return false;
    }
    return true;
}

bool testSortOne(SortFunc sort)
{
    const int a = 0;
    vector<int> data = { a };
    sort(data);
    if (data.size() != 1 || data[0] != a) {
        std::cout << "\33[31m";
        std::cout << "test failed with one element\n";
        std::cout << "\33[0m";
        return false;
    }
    return true;
}

bool testSortOnce(SortFunc sort, int shuffle_seed)
{
    auto unsorted = vec_ref;
    VecGen::randomShuffle(unsorted, shuffle_seed);
    auto sorted = unsorted;
    sort(sorted);
    for (size_t i = 0; i < vec_ref.size(); ++i)
        if (vec_ref[i] != sorted[i]) {
            std::cout << "\33[31m";
            std::cout << "test failed with seed: " << shuffle_seed << '\n';
            std::cout << "    origin: " << unsorted << '\n';
            std::cout << "    result: " << sorted << '\n';
            std::cout << "\33[0m";
            return false;
        }
    return true;
}

void testSort(SortFunc sort)
{
    if (!testSortEmpty(sort)
        || !testSortOne(sort))
        return;
    for (int i = 0; i < 100; ++i) {
        if (!testSortOnce(sort, i))
            return;
    }
    std::cout << "all test passed" << '\n';
}

} //namespace
