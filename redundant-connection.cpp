#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <numeric>
#include <vector>

using namespace std;

// https://leetcode.com/problems/redundant-connection/description/?envType=daily-question&envId=2025-01-29

class Solution {
public:
  vector<int> findRedundantConnection(vector<vector<int>> &edges) {
    int n = edges.size();
    vector<int> disjointSet(n + 1);
    iota(disjointSet.begin(), disjointSet.end(), 0);
    for (auto &e : edges) {
      if (Solution::hasMatchingParent(disjointSet, e[0], e[1])) {
        return e;
      }
      Solution::disjointUnion(disjointSet, e[0], e[1]);
    }
    return vector<int>{1, 0};
  }

  static int getDisjointParent(vector<int> &disjointSet, int index) {
    int parent = disjointSet[index];
    if (parent == index) {
      return index;
    }
    parent = getDisjointParent(disjointSet, parent);
    disjointSet[index] = parent;
    return parent;
  }

  static void disjointUnion(vector<int> &disjointSet, int a, int b) {
    int ap = Solution::getDisjointParent(disjointSet, a);
    int bp = Solution::getDisjointParent(disjointSet, b);
    disjointSet[bp] = ap;
  }

  static bool hasMatchingParent(vector<int> &disjointSet, int a, int b) {
    return Solution::getDisjointParent(disjointSet, a) ==
           Solution::getDisjointParent(disjointSet, b);
  }
};

int main() {

  struct TestCase {
    vector<vector<int>> edges;
    vector<int> out;
  };

  vector<TestCase> testCases = {
      /*{{{1, 2}, {1, 3}, {2, 3}}, {2, 3}},*/
      /*{{{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}}, {1, 4}},*/
      {{{1, 4}, {3, 4}, {1, 3}, {1, 2}, {4, 5}}, {1, 3}},
  };

  Solution obj = Solution{};

  for (auto tc : testCases) {
    auto answer = obj.findRedundantConnection(tc.edges);
    auto passed = answer == tc.out;
    fmt::println("{} | {} | {} - {}", passed, answer, tc.edges, tc.out);
  }
}
