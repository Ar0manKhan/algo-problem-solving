#include <algorithm>
#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <numeric>
#include <vector>

using namespace std;

// https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/description/?envType=daily-question&envId=2025-01-25

class Solution {
public:
  // completely new deepseek solution
  vector<int> lexicographicallySmallestArray(vector<int> &nums, int limit) {
    int n = nums.size();
    if (n == 1)
      return nums;

    // Step 1: Pair values with original indices and sort by value
    vector<pair<int, int>> sortedPairs;
    for (int i = 0; i < n; ++i) {
      sortedPairs.emplace_back(nums[i], i);
    }
    sort(sortedPairs.begin(), sortedPairs.end());

    vector<int> result(n);
    int start = 0; // Start index of the current group

    // Step 2: Group elements and assign sorted values to sorted indices
    for (int i = 1; i <= n; ++i) {
      // Check if current element continues the group
      if (i < n && sortedPairs[i].first - sortedPairs[i - 1].first <= limit) {
        continue;
      }

      // Collect indices in the current group [start, i-1]
      vector<int> groupIndices;
      groupIndices.reserve(i - start);
      for (int j = start; j < i; ++j) {
        groupIndices.push_back(sortedPairs[j].second);
      }

      // Step 3: Sort indices to determine their order in the result
      sort(groupIndices.begin(), groupIndices.end());

      // Step 4: Assign sorted values to sorted indices
      for (int k = 0; k < groupIndices.size(); ++k) {
        result[groupIndices[k]] = sortedPairs[start + k].first;
      }

      start = i; // Move to the next group
    }

    return result;
  }

  // deepsek optimized my v2 code and few of my optimization as well
  /*
  vector<int> lexicographicallySmallestArray(const vector<int> &nums,
                                             int limit) {
    const int n = nums.size();
    if (n == 1)
      return nums;

    vector<int> sortedIndex(n);
    iota(sortedIndex.begin(), sortedIndex.end(), 0);
    sort(sortedIndex.begin(), sortedIndex.end(),
         [&nums](int lhs, int rhs) { return nums[lhs] < nums[rhs]; });

    vector<int> queueIndex(n);
    vector<vector<int>> queues;
    vector<int> newQueue;
    int currentQi = 0;

    // Process first element
    int prevNum = nums[sortedIndex[0]];
    newQueue.push_back(prevNum);
    queueIndex[sortedIndex[0]] = currentQi;

    for (int i = 1; i < n; ++i) {
      const int currentItem = sortedIndex[i];
      const int currentNum = nums[currentItem];

      if (currentNum - prevNum > limit) {
        queues.emplace_back(std::move(newQueue));
        ++currentQi;
      }

      newQueue.push_back(currentNum);
      queueIndex[currentItem] = currentQi;
      prevNum = currentNum;
    }

    // Add the last group
    queues.emplace_back(std::move(newQueue));
    vector<int> queueCurrent(queues.size(), 0);

    vector<int> result(n);
    for (int i = 0; i < n; ++i) {
      const int qi = queueIndex[i];
      result[i] = queues[qi][queueCurrent[qi]++];
    }

    return result;
  }
  */

  // my v2 code
  /*
  vector<int> lexicographicallySmallestArray(const vector<int> &nums,
                                             int limit) {
    int n = nums.size();
    if (n == 1)
      return nums;

    vector<int> sortedIndex(n);
    iota(sortedIndex.begin(), sortedIndex.end(), 0);
    sort(sortedIndex.begin(), sortedIndex.end(),
         [&nums](int lhs, int rhs) { return nums[lhs] < nums[rhs]; });

    vector<int> queueIndex(n, -1);
    vector<vector<int>> queues;
    // this will be the current pop index for each queue
    vector<int> queueCurrent;
    vector<int> newQueue;
    int currentQi = 0;

    int prevItem = sortedIndex[0];
    int prevNum = nums[prevItem];
    newQueue.push_back(prevNum);
    queueIndex[prevItem] = currentQi;

    for (int i = 1; i < n; i++) {
      int currentItem = sortedIndex[i];
      int currentNum = nums[currentItem];
      if (currentNum - prevNum > limit) {
        queues.push_back(newQueue);
        queueCurrent.push_back(0);
        newQueue = vector<int>();
        currentQi++;
      }
      newQueue.push_back(currentNum);
      queueIndex[currentItem] = currentQi;
      prevItem = currentItem;
      prevNum = currentNum;
    }
    queues.push_back(newQueue);
    queueCurrent.push_back(0);

    vector<int> result(n);
    for (int i = 0; i < n; ++i) {
      int qi = queueIndex[i];
      result[i] = (qi == -1) ? nums[i] : queues[qi][queueCurrent[qi]++];
    }

    return result;
  }
  */

  //==================================================

  /*
  // deepseek version (with no algo improvment)
  vector<int> lexicographicallySmallestArray(const vector<int> &nums,
                                             int limit) {
    int n = nums.size();
    if (n == 1)
      return nums;

    vector<int> sortedIndex(n);
    iota(sortedIndex.begin(), sortedIndex.end(), 0);
    sort(sortedIndex.begin(), sortedIndex.end(),
         [&nums](int lhs, int rhs) { return nums[lhs] < nums[rhs]; });

    struct NeighborLL {
      int left = -1;
      int right = -1;
    };
    vector<NeighborLL> neighbors(n);

    for (int i = 1; i < n; ++i) {
      int prev = sortedIndex[i - 1];
      int curr = sortedIndex[i];
      if (nums[curr] - nums[prev] <= limit) {
        neighbors[curr].left = prev;
        neighbors[prev].right = curr;
      }
    }

    vector<int> queueIndex(n, -1);
    vector<vector<int>> queues;
    vector<int> queueCurrent;

    for (int i = 0; i < n; ++i) {
      NeighborLL &v = neighbors[i];
      if ((v.left == -1 && v.right == -1) || queueIndex[i] != -1)
        continue;

      int qIdx = queues.size();
      queueIndex[i] = qIdx;
      vector<int> newQ;

      // Collect left elements in reverse order
      vector<int> leftElements;
      for (int temp = v.left; temp != -1; temp = neighbors[temp].left) {
        leftElements.push_back(nums[temp]);
        queueIndex[temp] = qIdx;
      }
      reverse(leftElements.begin(), leftElements.end());
      newQ.insert(newQ.end(), leftElements.begin(), leftElements.end());

      // Add current element
      newQ.push_back(nums[i]);

      // Collect right elements
      for (int temp = v.right; temp != -1; temp = neighbors[temp].right) {
        newQ.push_back(nums[temp]);
        queueIndex[temp] = qIdx;
      }

      queues.push_back(std::move(newQ));
      queueCurrent.push_back(0);
    }

    vector<int> result(n);
    for (int i = 0; i < n; ++i) {
      int qi = queueIndex[i];
      result[i] = (qi == -1) ? nums[i] : queues[qi][queueCurrent[qi]++];
    }

    return result;
  }
  */

  //==================================================

  /*
  vector<int> lexicographicallySmallestArray(vector<int> &nums, int limit) {
    auto n = nums.size();
    if (n == 1)
      return nums;
    vector<int> sortedIndex(n);
    for (size_t i = 0; i < n; i++) {
      sortedIndex[i] = i;
    }
    sort(sortedIndex.begin(), sortedIndex.end(),
         [&nums](const int lhs, const int rhs) {
           return nums[lhs] < nums[rhs];
         });

    struct NeighborLL {
      int left, right;
    };

    vector<NeighborLL> neighbors(n);

    for (size_t i = 1; i < n; i++) {
      int prev = sortedIndex[i - 1];
      int curr = sortedIndex[i];

      if (nums[curr] - nums[prev] <= limit) {
        neighbors[curr].left = prev;
        neighbors[prev].right = curr;
      } else {
        neighbors[curr].left = -1;
        neighbors[prev].right = -1;
      }
    }
    neighbors[sortedIndex[0]].left = -1;
    neighbors[sortedIndex[n - 1]].right = -1;

    vector<int> queueIndex(n, -1);
    vector<deque<int>> queues;

    for (size_t i = 0; i < n; i++) {
      auto &v = neighbors[i];
      // if there is no neighbor or queue is already made, then don't do
      // anything
      if ((v.left == -1 && v.right == -1) || queueIndex[i] != -1) {
        continue;
      }

      // create a new queue, append it to queeus, and get its idx
      deque<int> newQ;
      int qIdx = queues.size();
      queueIndex[i] = qIdx;

      newQ.push_back(nums[i]);

      int temp = v.left;
      while (temp != -1) {
        newQ.push_front(nums[temp]);
        queueIndex[temp] = qIdx;
        temp = neighbors[temp].left;
      }

      temp = v.right;
      while (temp != -1) {
        newQ.push_back(nums[temp]);
        queueIndex[temp] = qIdx;
        temp = neighbors[temp].right;
      }
      queues.push_back(newQ);
    }

    vector<int> result(n);
    for (size_t i = 0; i < n; i++) {
      int qi = queueIndex[i];
      if (qi == -1) {
        result[i] = nums[i];
      } else {
        result[i] = queues[qi].front();
        queues[qi].pop_front();
      }
    }

    return result;
  }
*/
};

int main() {

  struct TestCase {
    vector<int> nums;
    int limit;
    vector<int> out;
  };

  vector<TestCase> testCases = {{{1, 5, 3, 9, 8}, 2, {1, 3, 5, 8, 9}},
                                {
                                    {1, 7, 6, 18, 2, 1},
                                    3,
                                    {1, 6, 7, 18, 1, 2},
                                },
                                {{1, 7, 28, 19, 10}, 3, {1, 7, 28, 19, 10}}

  };

  Solution obj = Solution{};

  for (auto tc : testCases) {
    auto answer = obj.lexicographicallySmallestArray(tc.nums, tc.limit);
    auto passed = answer == tc.out;
    fmt::println("{} | {} | {} {} {}", passed, answer, tc.nums, tc.limit,
                 tc.out);
    /*cout << (passed ? "yes" : "no") << " | " << answer << " | " << tc <<
     * endl;*/
  }

  return 0;
}
