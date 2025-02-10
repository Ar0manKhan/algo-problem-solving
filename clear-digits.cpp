#include <algorithm>
#include <fmt/base.h>
#include <fmt/core.h>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  string clearDigits(string s) {
    string ss;
    ss.reserve(s.size());

    int skipCount = 0;

    for (string::reverse_iterator rit = s.rbegin(); rit != s.rend(); ++rit) {
      if ('0' <= *rit && *rit <= '9') {
        skipCount++;
      } else if (skipCount > 0) {
        skipCount--;
      } else {
        ss.push_back(*rit);
      }
    }

    reverse(ss.begin(), ss.end());

    return ss;
  }
};

struct TestCase {
  string input;
  string expectedOutput;
};

int main() {
  Solution sol;

  vector<TestCase> testCases = {{.input = "abc", .expectedOutput = "abc"},
                                {.input = "cb34", .expectedOutput = ""}};

  fmt::println("Running test cases:");

  for (size_t i = 0; i < testCases.size(); ++i) {
    TestCase &testCase = testCases[i];
    string actualOutput = sol.clearDigits(testCase.input);
    bool passed = actualOutput == testCase.expectedOutput;
    fmt::println("Test Case {}:", i + 1);
    fmt::println("  Input: \"{}\"", testCase.input);
    fmt::println("  Expected Output: \"{}\"", testCase.expectedOutput);
    fmt::println("  Actual Output: \"{}\"", actualOutput);
    if (passed) {
      fmt::println("  Status: Passed");
    } else {
      fmt::println("  Status: Failed");
    }
  }

  return 0;
}
