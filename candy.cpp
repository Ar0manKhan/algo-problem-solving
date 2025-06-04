#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>

using namespace std;

// Define the Solution class as provided
class Solution {
public:
  int candy(vector<int> &ratings) {

    int n = ratings.size();
    int n1 = n - 1;

    vector<int> candy_count(n, 1);

    for (int i = 0; i < n1; i++) {
      int curr = candy_count[i];
      if (ratings[i] < ratings[i + 1] && curr >= candy_count[i + 1]) {
        candy_count[i + 1] = (curr + 1);
      }
    }

    for (int i = n1; i > 0; i--) {
      int curr = candy_count[i];
      if (ratings[i] < ratings[i - 1] && curr >= candy_count[i - 1]) {
        candy_count[i - 1] = (curr + 1);
      }
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
      result += candy_count[i];
    }

    return result;
  }
};

// Structure to hold test cases
struct TestCase {
  std::vector<int> ratings;
  int expected_output;
};

int main() {
  // Create a vector of test cases
  std::vector<TestCase> testCases = {// Example 1
                                     {{1, 0, 2}, 5},
                                     // Example 2
                                     {{1, 2, 2}, 4}};

  Solution solution;

  // Loop through test cases and run tests
  for (size_t i = 0; i < testCases.size(); ++i) {
    auto &testCase = testCases[i];

    // Call the function to be tested
    int actual_output = solution.candy(testCase.ratings);

    // Display results
    fmt::print("Test Case {}:\n", i + 1);

    fmt::print("  Input: ratings = [");
    for (size_t j = 0; j < testCase.ratings.size(); ++j) {
      fmt::print("{}", testCase.ratings[j]);
      if (j < testCase.ratings.size() - 1) {
        fmt::print(", ");
      }
    }
    fmt::print("]\n");

    fmt::print("  Expected Output: {}\n", testCase.expected_output);
    fmt::print("  Actual Output:   {}\n", actual_output);

    if (actual_output == testCase.expected_output) {
      fmt::print("  Result: PASSED\n\n");
    } else {
      fmt::print("  Result: FAILED\n\n");
    }
  }

  return 0;
}
