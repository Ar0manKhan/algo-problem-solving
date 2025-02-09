#include <fmt/core.h>
#include <set>
#include <unordered_map>
#include <vector>

class NumberContainers {
private:
  std::unordered_map<int, int> indexToNum;
  std::unordered_map<int, std::set<int>> numToIndexes;

public:
  NumberContainers() {}

  void change(int index, int number) {
    // checking if in current index, some other number exists,
    // if yes then delete that number
    auto prevNumber = this->indexToNum.find(index);
    if (prevNumber != this->indexToNum.end()) {
      this->numToIndexes[prevNumber->second].erase(index);
    }

    this->indexToNum[index] = number;
    this->numToIndexes[number].insert(index);
  }

  int find(int number) {
    auto itr = this->numToIndexes.find(number);
    // checking if this number has entry, if not then return -1;
    if (itr == this->numToIndexes.end() || itr->second.empty()) {
      return -1;
    }
    return *(itr->second.begin());
  }
};

struct TestCase {
  std::vector<std::string> methods;
  std::vector<std::vector<int>> args;
  std::vector<int> expected;
};

int main() {
  std::vector<TestCase> testCases = {{
      {"NumberContainers", "find", "change", "change", "change", "change",
       "find", "change", "find"},
      {{}, {10}, {2, 10}, {1, 10}, {3, 10}, {5, 10}, {10}, {1, 20}, {10}},
      {0, -1, 0, 0, 0, 0, 1, 0, 2} // replace 0 with null for the first element
  }};

  for (size_t i = 0; i < testCases.size(); ++i) {
    NumberContainers nc;
    bool passed = true;
    for (size_t j = 0; j < testCases[i].methods.size(); ++j) {
      int result;
      if (testCases[i].methods[j] == "NumberContainers") {
        continue;
      } else if (testCases[i].methods[j] == "find") {
        result = nc.find(testCases[i].args[j][0]);
      } else { // change
        nc.change(testCases[i].args[j][0], testCases[i].args[j][1]);
        result = 0; // Dummy value for change method
      }

      if (j > 0) { // skip the first element as it's constructor call.
        if (result != testCases[i].expected[j]) {
          fmt::print(
              "Test case {} failed at method {}: Expected {}, but got {}\n",
              i + 1, testCases[i].methods[j], testCases[i].expected[j], result);
          passed = false;
          break;
        }
      }
    }
    if (passed) {
      fmt::print("Test case {} passed\n", i + 1);
    }
  }

  return 0;
}
