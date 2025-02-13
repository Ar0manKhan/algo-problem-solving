#include <algorithm>
#include <array>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>

using namespace std;

class TwoLargest {
public:
  int a = 0, b = 0;
  inline void insert(int n) {
    if (n > a) {
      b = a;
      a = n;
    } else if (n > b) {
      b = n;
    }
  }

  inline int getSum() const { return (a == 0 || b == 0) ? -1 : a + b; }
};

class Solution {
public:
  int maximumSum(vector<int> &nums) {
    array<TwoLargest, 82> twoLargest;

    for (const int x : nums) {
      twoLargest[digitSum(x)].insert(x);
    }

    int maxVal = -1;
    int i = 0;
    for (const TwoLargest &e : twoLargest) {
      maxVal = max(maxVal, e.getSum());
    }
    return maxVal;
  }

  inline int digitSum(int n) const {
    int result = 0;
    while (n > 0) {
      result += (n % 10);
      n /= 10;
    }
    return result;
  }
};

struct TestCase {
  vector<int> nums;
  int expected;
};

int main() {
  vector<TestCase> testCases = {
      {{18, 43, 36, 13, 7}, 54},
      /*{{10, 12, 19, 14}, -1}*/
  };

  Solution sol;

  for (size_t i = 0; i < testCases.size(); ++i) {
    int result = sol.maximumSum(testCases[i].nums);
    bool passed = (result == testCases[i].expected);

    fmt::print("Test Case {}:\n", i + 1);
    fmt::print("  Input: nums = {}\n", testCases[i].nums);
    fmt::print("  Expected: {}\n", testCases[i].expected);
    fmt::print("  Result: {}\n", result);
    fmt::print("  Passed: {}\n", passed);
    fmt::print("\n");
  }

  return 0;
}
