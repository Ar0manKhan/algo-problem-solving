#include <fmt/base.h>
#include <fmt/core.h>
#include <string>
#include <vector>

using namespace std;

// Definition for the Solution class
class Solution {
public:
  std::string gcdOfStrings(std::string str1, std::string str2) {
    if (str1 == "" || str2 == "") {
      return "";
    }
    string l = str1, s = str2;
    if (str1.size() < str2.size()) {
      l = str2;
      s = str1;
    }

    int m = 0;
    int roundCount = l.size() / s.size();
    for (int i = 0; i < roundCount; i++) {
      for (int j = 0; j < s.size(); j++, m++) {
        if (l[m] != s[j]) {
          return "";
        }
      }
    }

    if (l.size() == s.size() * roundCount) {
      return s;
    }

    return gcdOfStrings(s, l.substr(roundCount * s.size()));
  }
};

// Structure to hold a test case
struct TestCase {
  std::string str1;
  std::string str2;
  std::string expected;
};

int main() {
  // Array/Vector of test cases
  std::vector<TestCase> testCases = {
      {"ABCABC", "ABC", "ABC"},
      {"ABABAB", "ABAB", "AB"},
      {"LEET", "CODE", ""},
      {"TAUXXTAUXXTAUXXTAUXXTAUXX",
       "TAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXX", "TAUXX"},
  };

  Solution sol;

  // Loop through test cases
  for (size_t i = 0; i < testCases.size(); ++i) {
    const auto &tc = testCases[i];
    std::string result = sol.gcdOfStrings(tc.str1, tc.str2);

    bool passed = (result == tc.expected);

    fmt::print("Test Case {}: str1={}, str2={}\n", i + 1, tc.str1, tc.str2);
    fmt::print("Expected: \"{}\", Got: \"{}\"\n", tc.expected, result);
    fmt::print("Result: {}\n\n", passed ? "PASSED" : "FAILED");
  }

  return 0;
}
