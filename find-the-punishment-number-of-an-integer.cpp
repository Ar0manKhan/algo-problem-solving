#include <fmt/format.h>
#include <utility>
#include <vector>

using namespace std;

constexpr pair<int, int> punishment_cached[] = {
    {1, 1},           {9, 82},        {10, 182},      {36, 1478},
    {45, 3503},       {55, 6528},     {82, 13252},    {91, 21533},
    {99, 31334},      {100, 41334},   {235, 96559},   {297, 184768},
    {369, 320929},    {370, 457829},  {379, 601470},  {414, 772866},
    {657, 1204515},   {675, 1660140}, {703, 2154349}, {756, 2725885},
    {792, 3353149},   {909, 4179430}, {918, 5022154}, {945, 5915179},
    {964, 6844475},   {990, 7824575}, {991, 8806656}, {999, 9804657},
    {1000, 10804657},
};

class Solution {
public:
  int punishmentNumber(int n) {
    int prevVal = 0;
    for (const auto &e : punishment_cached) {
      if (e.first > n)
        return prevVal;
      prevVal = e.second;
    }
    return prevVal;
  }
};

struct TestCase {
  int n;
  int expectedOutput;
};

int main() {
  Solution sol;

  vector<TestCase> testCases = {
      {10, 182},
      {37, 1478},
  };

  for (int i = 0; i < testCases.size(); ++i) {
    TestCase &testCase = testCases[i];
    int result = sol.punishmentNumber(testCase.n);
    bool passed = result == testCase.expectedOutput;
    fmt::println("Test Case {}:", i + 1);
    fmt::println("  Input: n = {}", testCase.n);
    fmt::println("  Expected Output: {}", testCase.expectedOutput);
    fmt::println("  Actual Output: {}", result);
    if (passed) {
      fmt::println("  Status: PASSED");
    } else {
      fmt::println("  Status: FAILED");
    }
    fmt::println("");
  }

  return 0;
}

/**
 * wrote this horrible python code to pre-calculate punishment upto 1k
 * def generate_patterns(n: int):
    arr = [[1]]
    for i in range(n-1):
        new_arr = []
        for v in arr:
            a = v.copy()
            b = v.copy()
            a.append(1)
            x = b.pop()
            b.append(x+1)
            new_arr.append(a)
            new_arr.append(b)
        arr = new_arr
    return arr


def possibleSum(num, target):
    sn = str(num)
    patterns = generate_patterns(len(sn))

    for p in patterns:
        n_generator = sn.__iter__()
        current_number = 0
        for i in p:
            sub_string = ""
            for j in range(i):
                sub_string += n_generator.__next__()
            current_number += int(sub_string)
        if current_number == target:
            return True
    return False


if __name__ == "__main__":
    current_sum = 0
    for i in range(1, 100000000):
        if possibleSum(i*i, i):
            current_sum += i*i
            print("{", i, ",", current_sum, "},")
*/
