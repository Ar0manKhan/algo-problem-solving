#include <algorithm>
#include <cstddef>
#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>

using namespace std;

// Define the solution class as provided
class Solution {
public:
  bool isZeroArray(vector<int> &nums, vector<vector<int>> &queries) {
    vector<int> count(nums.size() + 1);
    for (auto const &e : queries) {
      const int start = e[0];
      const int end = e[1];
      count[start]++;
      count[end + 1]--;
    }
    int prev = 0;
    for (size_t i = 0; i < count.size(); i++) {
      count[i] += prev;
      prev = count[i];
    }
    fmt::println("count:{}", count);
    size_t index = 0;
    return all_of(nums.begin(), nums.end(),
                  [&count, &index](int num) { return num <= count[index++]; });
  }
};

/*
 * Prefix sum
  bool isZeroArray(vector<int> &nums, vector<vector<int>> &queries) {
    vector<int> count(nums.size());
    for (vector<int> e : queries) {
      int start = e[0];
      int end = e[1];
      for (int i = start; i <= end; i++) {
        count[i]++;
      }
    }
    for (size_t i = 0; i < nums.size(); i++) {
      int e = count[i];
      if (e < nums[i])
        return false;
    }
    return true;
  }
*/

// Structure to hold a single test case
struct TestCase {
  std::vector<int> nums;
  std::vector<std::vector<int>> queries;
  bool expected;
};

int main() {
  std::vector<TestCase> testCases = {{// Example 1
                                      {1, 0, 1},
                                      {{0, 2}},
                                      true},
                                     {// Example 2
                                      {4, 3, 2, 1},
                                      {{1, 3}, {0, 2}},
                                      false},
                                     {{3}, {{0, 0}, {0, 0}}, false}};

  Solution sol;

  for (size_t i = 0; i < testCases.size(); ++i) {
    TestCase &tc = testCases[i];
    // Create copies of nums and queries as the function might modify them
    std::vector<int> nums_copy = tc.nums;
    std::vector<std::vector<int>> queries_copy = tc.queries;

    bool result = sol.isZeroArray(nums_copy, queries_copy);

    bool passed = (result == tc.expected);

    fmt::print("Test Case {}:\n", i + 1);
    fmt::print("  Inputs:\n");
    fmt::print("    nums: [");
    for (size_t j = 0; j < tc.nums.size(); ++j) {
      fmt::print("{}", tc.nums[j]);
      if (j < tc.nums.size() - 1)
        fmt::print(", ");
    }
    fmt::print("]\n");
    fmt::print("    queries: [");
    for (size_t j = 0; j < tc.queries.size(); ++j) {
      fmt::print("[{}, {}]", tc.queries[j][0], tc.queries[j][1]);
      if (j < tc.queries.size() - 1)
        fmt::print(", ");
    }
    fmt::print("]\n");

    fmt::print("  Expected Output: {}\n", tc.expected);
    fmt::print("  Actual Output:   {}\n", result);
    fmt::print("  Result: {}\n", passed ? "PASSED" : "FAILED");
    fmt::print("--------------------\n");
  }

  return 0;
}
