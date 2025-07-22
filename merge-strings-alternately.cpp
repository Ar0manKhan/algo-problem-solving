#include <fmt/core.h>
#include <fmt/format.h>
#include <string>
#include <vector>

using namespace std;

// Definition of the Solution class as provided (user will implement the logic)
class Solution {
public:
  std::string mergeAlternately(std::string word1, std::string word2) {
    // User will implement the solution here
    // Returning an empty string as a placeholder
    string result;
    result.resize(word1.size() + word2.size());

    int a = 0, b = 0, c = 0;

    while (c < result.size()) {
      if (a < word1.size()) {
        result[c++] = word1[a++];
      }
      if (b < word2.size()) {
        result[c++] = word2[b++];
      }
    }

    return result;
  }
};

// Structure to hold test case data
struct TestCase {
  std::string word1;
  std::string word2;
  std::string expected_output;
};

int main() {
  // Vector of test cases based on problem examples
  std::vector<TestCase> testCases = {
      {"abc", "pqr", "apbqcr"},
      {"ab", "pqrs", "apbqrs"},
      {"abcd", "pq", "apbqcd"},
  };

  Solution solution;
  int test_count = 0;
  int passed_count = 0;

  fmt::print("Testing Solution::mergeAlternately...\n");

  for (const auto &tc : testCases) {
    test_count++;
    std::string actual_output = solution.mergeAlternately(tc.word1, tc.word2);

    bool passed = (actual_output == tc.expected_output);
    if (passed) {
      passed_count++;
    }

    fmt::print("Test Case {}:\n", test_count);
    fmt::print("  Input: word1 = \"{}\", word2 = \"{}\"\n", tc.word1, tc.word2);
    fmt::print("  Expected Output: \"{}\"\n", tc.expected_output);
    fmt::print("  Actual Output:   \"{}\"\n", actual_output);
    fmt::print("  Result: {}\n", passed ? "PASSED" : "FAILED");
    fmt::print("---\n");
  }

  fmt::print("Summary: {}/{} tests passed.\n", passed_count, test_count);

  return 0;
}
