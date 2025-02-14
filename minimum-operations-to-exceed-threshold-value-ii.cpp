#include <cstddef>
#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  int minOperations(vector<int> &nums, int k) {
    priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int>>
        pq(nums.begin(), nums.end());
    int opsCount = 0;
    while (pq.top() < k) {
      opsCount++;
      unsigned int x = pq.top();
      pq.pop();
      unsigned int y = pq.top();
      pq.pop();
      unsigned int v = x + 2 * y;
      fmt::println("x {}, y {}, v{}", x, y, v);
      pq.push(v);
    }

    return opsCount;
  }
};

struct TestCase {
  vector<int> nums;
  int k;
  int expected;
};

int main() {
  vector<TestCase> testCases = {
      /*{.nums = {2, 11, 10, 1, 3}, .k = 10, .expected = 2},*/
      /*{.nums = {1, 1, 2, 4, 9}, .k = 20, .expected = 4},*/
      /*{{999999999, 999999999, 999999999}, 1000000000, 2},*/
      {{97, 73, 5, 78}, 98, 3}

  };

  Solution sol;

  for (size_t i = 0; i < testCases.size(); ++i) {
    auto &testCase = testCases[i];
    int result = sol.minOperations(testCase.nums, testCase.k);

    if (result == testCase.expected) {
      fmt::print("Test case {}: Passed\n", i + 1);
    } else {
      fmt::print("Test case {}: Failed\n", i + 1);
      fmt::print("  Input: nums = {}, k = {}\n", testCase.nums, testCase.k);
      fmt::print("  Expected: {}\n", testCase.expected);
      fmt::print("  Actual: {}\n", result);
    }
  }

  return 0;
}
