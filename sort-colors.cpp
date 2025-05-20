#include <fmt/core.h>
#include <fmt/ranges.h> // For printing vectors
#include <vector>

// Definition for the Solution class (user will implement the sorting logic)
class Solution {
public:
  void sortColors(std::vector<int> &nums) {
    uint colorCount[3] = {0, 0, 0};
    for (int v : nums) {
      colorCount[v]++;
      uint idx = 0;
      uint i = 0;
      for (; i < colorCount[0]; i++)
        nums[i] = 0;
      idx = i;
      for (i = 0; i < colorCount[1]; i++)
        nums[i + idx] = 1;
      idx += i;
      for (i = 0; i < colorCount[2]; i++)
        nums[i + idx] = 2;
    }
  }
};

// Structure to hold test case data
struct TestCase {
  std::vector<int> input_nums;
  std::vector<int> expected_nums;
};

int main() {
  std::vector<TestCase> testCases = {{// Example 1
                                      {2, 0, 2, 1, 1, 0},
                                      {0, 0, 1, 1, 2, 2}},
                                     {// Example 2
                                      {2, 0, 1},
                                      {0, 1, 2}}};

  Solution solution;

  for (size_t i = 0; i < testCases.size(); ++i) {
    std::vector<int> nums =
        testCases[i].input_nums; // Copy input as sortColors modifies in-place
    std::vector<int> initial_nums =
        testCases[i]
            .input_nums; // Keep a copy of the original input for printing
    const std::vector<int> &expected_nums = testCases[i].expected_nums;

    fmt::print("Test Case {}:\n", i + 1);
    fmt::print("  Input: {}\n", initial_nums);
    fmt::print("  Expected Output: {}\n", expected_nums);

    solution.sortColors(nums); // Call the function to be tested

    fmt::print("  Actual Output: {}\n", nums);

    if (nums == expected_nums) {
      fmt::print("  Result: PASSED\n\n");
    } else {
      fmt::print("  Result: FAILED\n\n");
    }
  }

  return 0;
}
