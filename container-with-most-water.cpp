#include <fmt/core.h> // For fmt::print
#include <vector>

using namespace std;

// Solution class as given, implementation is left for the user
class Solution {
public:
  int maxArea(std::vector<int> &height) {
    int hn = height.size();
    int i = 0, j = hn - 1;
    int res = 0;
    while (i < j) {
      res = max((j - i) * min(height[i], height[j]), res);
      if (height[i] < height[j])
        i++;
      else
        j--;
    }
    return res;
  }
};

// Structure to hold a single test case
struct TestCase {
  std::vector<int> height;
  int expected_output;
  std::string description; // Optional: for better logging
};

// Helper function to print a vector
template <typename T> std::string vector_to_string(const std::vector<T> &vec) {
  if (vec.empty()) {
    return "[]";
  }
  std::string s = "[";
  for (size_t i = 0; i < vec.size(); ++i) {
    s += fmt::format("{}", vec[i]);
    if (i < vec.size() - 1) {
      s += ",";
    }
  }
  s += "]";
  return s;
}

int main() {
  std::vector<TestCase> test_cases = {
      {// Example 1
       .height = {1, 8, 6, 2, 5, 4, 8, 3, 7},
       .expected_output = 49,
       .description = "Example 1"},
      {// Example 2
       .height = {1, 1},
       .expected_output = 1,
       .description = "Example 2"},
  };

  Solution sol;
  int passed_tests = 0;

  for (size_t i = 0; i < test_cases.size(); ++i) {
    auto &tc = test_cases[i];

    // Call the function to be tested
    int actual_output = sol.maxArea(tc.height);

    // Display results
    fmt::print("--- Test Case {} ({}) ---\n", i + 1, tc.description);
    fmt::print("Input: height = {}\n", vector_to_string(tc.height));
    fmt::print("Expected Output: {}\n", tc.expected_output);
    fmt::print("Actual Output: {}\n", actual_output);

    if (actual_output == tc.expected_output) {
      fmt::print("Result: PASSED\n\n");
      passed_tests++;
    } else {
      fmt::print("Result: FAILED\n\n");
    }
  }

  fmt::print("--- Test Summary ---\n");
  fmt::print("Total Tests: {}\n", test_cases.size());
  fmt::print("Passed: {}\n", passed_tests);
  fmt::print("Failed: {}\n", test_cases.size() - passed_tests);

  return 0;
}
