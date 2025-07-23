#include <climits>
#include <string>
#include <vector>

// Include fmt for logging. Make sure fmt library is linked.
// You might need to add `fmt/ranges.h` for easy printing of containers.
#include <fmt/core.h>
#include <fmt/ranges.h> // For printing std::vector easily

// The solution class definition
class Solution {
public:
  bool increasingTriplet(std::vector<int> &nums) {
    int a = INT_MAX, b = INT_MAX;
    for (int v : nums) {
      if (v <= a)
        a = v;
      else if (v <= b)
        b = v;
      else
        return true;
    }
    return false;
  }
};

// Structure to hold test case data
struct TestCase {
  std::vector<int> nums;
  bool expected_output;
  std::string description; // Optional: for better logging
};

int main() {
  // Array/Vector of test cases
  std::vector<TestCase> test_cases = {
      {.nums = {1, 2, 3, 4, 5},
       .expected_output = true,
       .description = "Example 1: Basic increasing sequence"},
      {.nums = {5, 4, 3, 2, 1},
       .expected_output = false,
       .description = "Example 2: Basic decreasing sequence"},
      {.nums = {2, 1, 5, 0, 4, 6},
       .expected_output = true,
       .description = "Example 3: Mixed sequence with a valid triplet"},
      // Add more test cases here if needed during development
  };

  Solution sol;
  int passed_count = 0;

  // Loop through the array and call the function to be tested
  for (size_t i = 0; i < test_cases.size(); ++i) {
    auto &tc = test_cases[i];

    // Call the function
    bool actual_output = sol.increasingTriplet(tc.nums);

    // Determine if the test case passed or failed
    bool passed = (actual_output == tc.expected_output);
    if (passed) {
      passed_count++;
    }

    // Display the result, inputs, and test case status
    fmt::print("--- Test Case {} ---\n", i + 1);
    fmt::print("Description: {}\n", tc.description);
    fmt::print("Input nums: {}\n", tc.nums);
    fmt::print("Expected Output: {}\n", tc.expected_output);
    fmt::print("Actual Output: {}\n", actual_output);
    fmt::print("Test Case Status: {}\n", passed ? "PASSED" : "FAILED");
    fmt::print("---------------------\n\n");
  }

  // Summary of test results
  fmt::print("Summary: {}/{} test cases passed.\n", passed_count,
             test_cases.size());

  return 0;
}
