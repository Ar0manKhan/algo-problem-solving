#include <algorithm>
#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>

using namespace std;

// https://leetcode.com/problems/making-a-large-island/description/?envType=daily-question&envId=2025-01-31

struct Coordinates {
  int x, y;
};

Coordinates directions[4] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
};

class Solution {
public:
  int largestIsland(vector<vector<int>> &grid) {
    int n = grid.size();
    vector<int> groupIdx(n * n);
    vector<int> islandSize;
    int groupNum = 0;
    islandSize.push_back(0);

    // go through each item in grid and run bfs
    // check for visited by groupIdx vector

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] && !groupIdx[i * n + j]) {
          groupNum++;
          Coordinates curr = {i, j};
          islandSize.push_back(dfs(grid, groupIdx, groupNum, curr, n));
        }
      }
    }

    int result = *max_element(islandSize.begin(), islandSize.end());
    vector<int> neiGroups;
    neiGroups.reserve(4);

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j]) {
          continue;
        }
        int currentRes = 1;
        for (auto &d : directions) {
          int nextI = i + d.x, nextJ = j + d.y;
          if (nextI < 0 || nextI >= n || nextJ < 0 || nextJ >= n) {
            continue;
          }
          int g = groupIdx[nextI * n + nextJ];
          // item found
          if (g &&
              find(neiGroups.begin(), neiGroups.end(), g) == neiGroups.end()) {
            neiGroups.push_back(g);
            currentRes += islandSize[g];
          }
        }
        neiGroups.clear();
        result = max(result, currentRes);
      }
    }

    return result;
  }

  static int dfs(vector<vector<int>> &grid, vector<int> &groupIdx, int groupNum,
                 Coordinates &start, int n) {
    vector<Coordinates> neiStack;
    neiStack.push_back(start);
    int islandSize = 0;

    while (neiStack.size()) {
      auto currentCord = neiStack.back();
      neiStack.pop_back();

      if (groupIdx[currentCord.x * n + currentCord.y]) {
        continue;
      }

      islandSize++;
      groupIdx[currentCord.x * n + currentCord.y] = groupNum;

      for (auto &d : directions) {
        Coordinates nextCoord = {currentCord.x + d.x, currentCord.y + d.y};
        if (nextCoord.x > -1 && nextCoord.x < n && nextCoord.y > -1 &&
            nextCoord.y < n && !groupIdx[nextCoord.x * n + nextCoord.y] &&
            grid[nextCoord.x][nextCoord.y]) {
          neiStack.push_back(nextCoord);
        }
      }
    }
    return islandSize;
  }
};

int main() {

  struct TestCase {
    vector<vector<int>> grid;
    int out;
  };

  vector<TestCase> testCases = {{{{1, 0}, {0, 1}}, 3},
                                {
                                    {{1, 1}, {1, 0}},
                                    4,
                                },
                                {
                                    {{
                                         1,
                                         1,
                                     },
                                     {
                                         1,
                                         1,
                                     }},
                                    4,
                                },
                                {{{0, 0, 0, 0, 0, 0, 0},
                                  {0, 1, 1, 1, 1, 0, 0},
                                  {0, 1, 0, 0, 1, 0, 0},
                                  {1, 0, 1, 0, 1, 0, 0},
                                  {0, 1, 0, 0, 1, 0, 0},
                                  {0, 1, 0, 0, 1, 0, 0},
                                  {0, 1, 1, 1, 1, 0, 0}},
                                 18}};

  Solution obj = Solution{};

  for (auto tc : testCases) {
    auto answer = obj.largestIsland(tc.grid);
    auto passed = answer == tc.out;
    fmt::println("{} | {} | {} - {}", passed, answer, tc.grid, tc.out);
  }
}
