#include <algorithm>
#include <cstddef>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>

using namespace std;

// Definition for the Solution class (to be implemented by the user)
class Solution {
public:
  std::vector<bool> kidsWithCandies(std::vector<int> &candies,
                                    int extraCandies) {
    int maxVal = *max_element(candies.begin(), candies.end());
    vector<bool> result(candies.size());
    int target = maxVal - extraCandies;
    for (size_t i = 0; i < candies.size(); i++) {
      result[i] = candies[i] >= target;
    }
    return result;
  }
};

// Structure to hold a single test case
struct TestCase {
  std::vector<int> candies;
  int extraCandies;
  std::vector<bool> expected;
};

// Function to compare two vectors<bool>
bool areVectorsEqual(const std::vector<bool> &v1, const std::vector<bool> &v2) {
  if (v1.size() != v2.size()) {
    return false;
  }
  for (size_t i = 0; i < v1.size(); ++i) {
    if (v1[i] != v2[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  // Create test cases based on the examples
  std::vector<TestCase> testCases = {
      {{2, 3, 5, 1, 3}, 3, {true, true, true, false, true}},
      {{4, 2, 1, 1, 2}, 1, {true, false, false, false, false}},
      {{12, 1, 12}, 10, {true, false, true}}};

  Solution solution;

  // Loop through test cases and run the solution
  for (size_t i = 0; i < testCases.size(); ++i) {
    auto &tc = testCases[i];

    fmt::print("--- Test Case {} ---\n", i + 1);
    fmt::print("Input:\n");
    fmt::print("  candies: {}\n", tc.candies);
    fmt::print("  extraCandies: {}\n", tc.extraCandies);
    fmt::print("Expected Output: {}\n", tc.expected);

    std::vector<bool> result =
        solution.kidsWithCandies(tc.candies, tc.extraCandies);

    fmt::print("Actual Output:   {}\n", result);

    if (areVectorsEqual(result, tc.expected)) {
      fmt::print("Test Case {} Passed\n", i + 1);
    } else {
      fmt::print("Test Case {} Failed\n", i + 1);
    }
    fmt::print("\n");
  }

  return 0;
}
