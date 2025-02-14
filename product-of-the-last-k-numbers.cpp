#include <fmt/core.h>
#include <string>
#include <vector>

using namespace std;

class ProductOfNumbers {
private:
  vector<int> productLadder;
  int totalProduct = 1;

public:
  void add(int num) {
    if (num == 0) {
      totalProduct = 1;
      productLadder.clear();
    } else {
      productLadder.push_back(totalProduct);
      totalProduct *= num;
    }
  }

  int getProduct(int k) {
    int sz = productLadder.size();
    if (sz >= k) {
      return totalProduct / productLadder[sz - k];
    } else {
      return 0;
    }
  }
};

struct TestCase {
  vector<string> operations;
  vector<vector<int>> operation_inputs;
  vector<int> expected_outputs;
};

int main() {
  vector<TestCase> testCases = {{
      {"ProductOfNumbers", "add", "add", "add", "add", "add", "getProduct",
       "getProduct", "getProduct", "add", "getProduct"},
      {{}, {3}, {0}, {2}, {5}, {4}, {2}, {3}, {4}, {8}, {2}},
      {0, 0, 0, 0, 0, 0, 20, 40, 0, 0, 32}
      // Using 0 to represent null output for add and constructor
  }};

  for (size_t i = 0; i < testCases.size(); ++i) {
    TestCase &testCase = testCases[i];
    /*fmt::print("Test Case {}\n", i + 1);*/

    ProductOfNumbers *productOfNumbers = nullptr;
    vector<int> actual_outputs;

    bool test_passed = true;

    for (size_t j = 0; j < testCase.operations.size(); ++j) {
      string operation = testCase.operations[j];
      vector<int> inputs = testCase.operation_inputs[j];
      int expected_output = testCase.expected_outputs[j];
      int actual_output = 0;

      if (operation == "ProductOfNumbers") {
        productOfNumbers = new ProductOfNumbers();
        actual_output = 0; // Representing null for constructor
      } else if (operation == "add") {
        if (productOfNumbers) {
          productOfNumbers->add(inputs[0]);
        }
        actual_output = 0; // Representing null for add
      } else if (operation == "getProduct") {
        if (productOfNumbers) {
          actual_output = productOfNumbers->getProduct(inputs[0]);
        } else {
          actual_output = -1; // Indicate error if productOfNumbers is null, but
                              // should not happen in valid test case
        }
      }

      actual_outputs.push_back(actual_output);

      if (operation == "getProduct") {
        if (actual_output != expected_output) {
          fmt::println(
              "Failed at idx: {} - actual output: {} - expected output: {}", j,
              actual_output, expected_output);
          test_passed = false;
          break;
        }
      }
    }

    if (test_passed) {
      fmt::print("Test Case {}: PASSED\n\n", i + 1);
    } else {
      fmt::print("Test Case {}: FAILED\n\n", i + 1);
    }
    if (productOfNumbers)
      delete productOfNumbers;
  }

  return 0;
}
