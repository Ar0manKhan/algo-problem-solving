#include <cstdint>
#include <fmt/core.h>
#include <sys/types.h>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> queryResults(int limit, vector<vector<int>> &queries) {
    int qn = queries.size();
    unordered_map<uint32_t, uint32_t> ballColor;
    unordered_map<uint32_t, uint32_t> colorCount;
    vector<int> result;
    result.reserve(qn);

    int distColorCount = 0;

    for (const auto &pair : queries) {
      const int a = pair[0];
      const int b = pair[1];

      // decreasing colorCount first and then comparing it to zero
      if (ballColor.find(a) != ballColor.end() &&
          --colorCount[ballColor[a]] == 0) {
        distColorCount--;
      }

      // increasing color count and then comparing to 1 which
      // check that this color is set right now only
      if (++colorCount[b] == 1) {
        distColorCount++;
      }

      ballColor[a] = b;
      result.push_back(distColorCount);
    }

    return result;
  }
};

struct TestCase {
  int limit;
  vector<vector<int>> queries;
  vector<int> expected;
};

int main() {
  vector<TestCase> testCases = {
      {4, {{1, 4}, {2, 5}, {1, 3}, {3, 4}}, {1, 2, 2, 3}},
      {4, {{0, 1}, {1, 2}, {2, 2}, {3, 4}, {4, 5}}, {1, 2, 2, 3, 4}}};

  Solution solution;
  for (size_t i = 0; i < testCases.size(); ++i) {
    vector<int> result =
        solution.queryResults(testCases[i].limit, testCases[i].queries);
    bool passed = true;
    if (result.size() != testCases[i].expected.size()) {
      passed = false;
    } else {
      for (size_t j = 0; j < result.size(); ++j) {
        if (result[j] != testCases[i].expected[j]) {
          passed = false;
          break;
        }
      }
    }

    fmt::print("Test Case {}: ", i + 1);
    fmt::print("Limit: {}, Queries: [", testCases[i].limit);
    for (size_t j = 0; j < testCases[i].queries.size(); ++j) {
      fmt::print("[{},{}]", testCases[i].queries[j][0],
                 testCases[i].queries[j][1]);
      if (j < testCases[i].queries.size() - 1) {
        fmt::print(", ");
      }
    }
    fmt::print("]\n");
    fmt::print("Expected: [");
    for (size_t j = 0; j < testCases[i].expected.size(); ++j) {
      fmt::print("{}", testCases[i].expected[j]);
      if (j < testCases[i].expected.size() - 1) {
        fmt::print(", ");
      }
    }
    fmt::print("]\n");
    fmt::print("Result: [");
    for (size_t j = 0; j < result.size(); ++j) {
      fmt::print("{}", result[j]);
      if (j < result.size() - 1) {
        fmt::print(", ");
      }
    }
    fmt::print("]\n");
    fmt::print("Passed: {}\n\n", passed);
  }

  return 0;
}
