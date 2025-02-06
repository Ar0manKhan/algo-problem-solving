#include <climits>
#include <deque>
#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>

using namespace std;

// https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/description/
// 2290

struct Coordinate {
  int x, y;
};

/*
struct CoordinatePairComparator {
  bool operator()(const pair<int, Coordinate> &a,
                  const pair<int, Coordinate> &b) const {
    // Return true if a should be placed after b in the heap
    return a.first > b.first;
  }
};
*/

class Solution {
public:
  int minimumObstacles(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    int tx = m - 1, ty = n - 1; // target x,y
    vector<int> costGrid(m * n, INT_MAX);
    costGrid[0] = 0;
    deque<Coordinate> dq;
    dq.emplace_back(Coordinate{0, 0});

    const vector<Coordinate> directions = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
    };

    while (!dq.empty()) {
      const auto cell = dq.front();
      dq.pop_front();
      const int currentCost = costGrid[cell.x * n + cell.y];

      if (cell.x == tx && cell.y == ty) {
        return currentCost;
      }

      for (const auto &d : directions) {
        const int nx = cell.x + d.x, ny = cell.y + d.y;
        if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
          continue;
        }
        const int nextCell = grid[nx][ny];
        const int nextCost = currentCost + nextCell;
        const int nextCurrCost = costGrid[nx * n + ny];
        if (nextCost < nextCurrCost) {
          costGrid[nx * n + ny] = nextCost;
          if (nextCell)
            dq.emplace_back(Coordinate{nx, ny});
          else
            dq.emplace_front(Coordinate{nx, ny});
        }
      }
    }
    return -1;
  }

  /*
  int minimumObstacles(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    int tx = m - 1, ty = n - 1; // target x,y
    vector<int> costGrid(m * n, -1);

    priority_queue<pair<int, Coordinate>, vector<pair<int, Coordinate>>,
                   CoordinatePairComparator>
        pq;
    const vector<Coordinate> directions = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
    };

    pq.emplace(0, Coordinate{0, 0});

    while (!pq.empty()) {
      const auto entry = pq.top();
      const auto &cell = entry.second;
      pq.pop();

      if (cell.x == tx && cell.y == ty) {
        return entry.first;
      }
      if (costGrid[cell.x * n + cell.y] != -1) {
        continue;
      }
      costGrid[cell.x * n + cell.y] = entry.first;

      for (const auto &d : directions) {
        const int nx = cell.x + d.x, ny = cell.y + d.y;
        if (nx < 0 || nx >= m || ny < 0 || ny >= n ||
            costGrid[nx * n + ny] != -1) {
          continue;
        }
        pq.emplace(entry.first + grid[nx][ny], Coordinate{nx, ny});
      }
    }

    return -1;
  }
  */
};

int main() {

  struct TestCase {
    vector<vector<int>> grid;
    int out;
  };

  vector<TestCase> testCases = {
      {{{0, 1, 1}, {1, 1, 0}, {1, 1, 0}}, 2},
      {{{0, 1, 0, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 0, 1, 0}}, 0}};

  Solution obj = Solution{};

  for (auto tc : testCases) {
    auto answer = obj.minimumObstacles(tc.grid);
    auto passed = answer == tc.out;
    fmt::println("{} | {} | {} - {}", passed, answer, tc.grid, tc.out);
  }

  return 0;
}
