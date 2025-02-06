#include <fmt/base.h>
#include <fmt/core.h>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  bool areAlmostEqual(std::string s1, std::string s2) {
    int n = s1.size();
    int nonMatching = 0;
    int invalidIdx = -1;
    for (int i = 0; i < n; i++) {
      if (s1[i] != s2[i]) {
        switch (nonMatching) {
        case 0:
          invalidIdx = i;
          break;
        case 1:
          if ((s1[invalidIdx] != s2[i]) || (s1[i] != s2[invalidIdx])) {
            return false;
          }
          break;
        default:
          return false;
        }
        nonMatching++;
      }
    }
    return nonMatching == 0 || nonMatching == 2;
  }
};

struct TestCase {
  std::string s1;
  std::string s2;
  bool expected;
};

int main() {
  std::vector<TestCase> testCases = {
      {"bank", "kanb", true},  {"attack", "defend", false},
      {"kelb", "kelb", true},  {"abc", "bca", false},
      {"abcd", "badc", false}, {"caa", "aaz", false},
      {"aa", "ac", false},

  };

  Solution solution;
  for (const auto &testCase : testCases) {
    bool result = solution.areAlmostEqual(testCase.s1, testCase.s2);
    fmt::print("s1: {}, s2: {}, Expected: {}, Result: {}\n", testCase.s1,
               testCase.s2, testCase.expected, result);
    if (result == testCase.expected) {
      fmt::print("Test case passed\n");
    } else {
      fmt::print("Test case failed\n");
    }
  }
  return 0;
}
