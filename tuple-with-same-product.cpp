#include <algorithm>
#include <fmt/core.h>
#include <sys/types.h>
#include <vector>

class Solution {
public:
  // using array as hash table
  // it wasn't optimal
  int tupleSameProduct(std::vector<int> &nums) {
    int n = nums.size();
    if (n < 4)
      return 0;

    std::sort(nums.begin(), nums.end());
    std::vector<u_int8_t> hashTable(nums[n - 1] * nums[n - 2] + 1);

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        hashTable[nums[i] * nums[j]]++;
      }
    }

    int result = 0;
    for (const auto &v : hashTable) {
      if (v > 1)
        result += (v * (v - 1));
    }

    return result * 4;
  }

  /*
  // using hash table
  int tupleSameProduct(std::vector<int> &nums) {
    int n = nums.size();
    if (n < 4)
      return 0;

    std::unordered_map<int, int> hashTable;
    hashTable.reserve((n * (n - 1)) / 2);

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        hashTable[nums[i] * nums[j]]++;
      }
    }

    int result = 0;
    for (const auto &pair : hashTable) {
      if (pair.second > 1)
        result += (pair.second * (pair.second - 1));
    }

    return result * 4;
  }
  */
};

struct TestCase {
  std::vector<int> nums;
  int expected;
};

int main() {
  std::vector<TestCase> testCases = {{{2, 3, 4, 6}, 8}, {{1, 2, 4, 5, 10}, 16}};

  Solution solution;

  for (auto &testCase : testCases) {
    int result = solution.tupleSameProduct(testCase.nums);
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
