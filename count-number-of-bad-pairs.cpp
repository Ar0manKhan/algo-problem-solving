#include <cstddef>
#include <fmt/base.h>
#include <fmt/core.h>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  long long countBadPairs(vector<int> &nums) {
    size_t n = nums.size();
    long long result = (n - 1) * (n) / 2;
    unordered_map<int, int> indexDiffCount;

    for (size_t i = 0; i < n; i++) {
      indexDiffCount[nums[i] - i]++;
    }

    for (size_t i = 0; i < n; i++) {
      result -= (--indexDiffCount[nums[i] - i]);
    }

    return result;
  }
};

struct TestCase {
  vector<int> nums;
  long long expected;
};

int main() {
  vector<TestCase> testCases = {{{4, 1, 3, 3}, 5}, {{1, 2, 3, 4, 5}, 0}};

  Solution solution;
  for (auto &testCase : testCases) {
    long long result = solution.countBadPairs(testCase.nums);
    fmt::print("Input: nums = [");
    for (size_t i = 0; i < testCase.nums.size(); ++i) {
      fmt::print("{}", testCase.nums[i]);
      if (i < testCase.nums.size() - 1) {
        fmt::print(", ");
      }
    }
    fmt::print("]\n");
    fmt::print("Output: {}\n", result);
    fmt::print("Expected: {}\n", testCase.expected);
    if (result == testCase.expected) {
      fmt::print("Test case passed\n");
    } else {
      fmt::print("Test case failed\n");
    }
    fmt::print("\n");
  }
  return 0;
}
