#include <fmt/base.h>
#include <fmt/core.h>   // For fmt::print
#include <fmt/ranges.h> // For printing vectors
#include <string>
#include <vector>

// Solution class definition as given
class Solution {
public:
  int compress(std::vector<char> &chars) {
    int count = 0;
    int i = 0;
    char prevV = chars[0];
    for (const char &v : chars) {
      if (v == prevV) {
        count++;
        continue;
      }
      chars[i++] = prevV;
      if (count > 1) {
        for (char d : std::to_string(count))
          chars[i++] = d;
      }
      count = 1;
      prevV = v;
    }
    chars[i++] = prevV;
    if (count > 1) {
      for (char d : std::to_string(count))
        chars[i++] = d;
    }
    return i;
  }
};

// Structure to hold a single test case
struct TestCase {
  std::vector<char> input_chars;
  int expected_length;
  std::vector<char>
      expected_modified_chars; // The state of chars after compression up to
                               // expected_length
  std::string description;

  // Constructor for convenience
  TestCase(std::vector<char> input, int len, std::vector<char> modified,
           std::string desc)
      : input_chars(std::move(input)), expected_length(len),
        expected_modified_chars(std::move(modified)),
        description(std::move(desc)) {}
};

int main() {
  Solution sol;

  // Array of test cases
  std::vector<TestCase> testCases = {
      TestCase({'a', 'a', 'b', 'b', 'c', 'c', 'c'}, 6,
               {'a', '2', 'b', '2', 'c', '3'},
               "Example 1: Multiple groups, with lengths > 1"),
      TestCase({'a'}, 1, {'a'}, "Example 2: Single character group"),
      TestCase(
          {'a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'}, 4,
          {'a', 'b', '1', '2'}, "Example 3: Group with length >= 10")};

  int passed_count = 0;
  int total_tests = testCases.size();

  // Loop through test cases
  for (int i = 0; i < total_tests; ++i) {
    TestCase &tc = testCases[i];

    // Make a copy of the input_chars because the function modifies it in-place
    std::vector<char> current_chars = tc.input_chars;

    fmt::print("--- Test Case {} ---\n", i + 1);
    fmt::print("Description: {}\n", tc.description);
    fmt::print("Input chars: {}\n", tc.input_chars); // Print original input

    int actual_length = sol.compress(current_chars);

    fmt::print("Expected length: {}\n", tc.expected_length);
    fmt::print("Actual length:   {}\n", actual_length);
    fmt::print("Expected modified chars (up to length {}): {}\n",
               tc.expected_length, tc.expected_modified_chars);
    fmt::print("Actual modified chars (up to length {}):   ", actual_length);

    // Print the actual modified array up to the returned length
    std::vector<char> actual_modified_sub;
    if (actual_length > 0 && actual_length <= current_chars.size()) {
      actual_modified_sub.assign(current_chars.begin(),
                                 current_chars.begin() + actual_length);
    }
    fmt::print("{}\n", actual_modified_sub);

    bool length_match = (actual_length == tc.expected_length);
    bool chars_match = true;

    if (length_match) {
      // Only compare modified characters if the lengths match,
      // otherwise, the character comparison is moot or might be out of bounds.
      if (actual_length == tc.expected_modified_chars.size()) {
        for (int j = 0; j < actual_length; ++j) {
          if (current_chars[j] != tc.expected_modified_chars[j]) {
            chars_match = false;
            break;
          }
        }
      } else {
        // This case should ideally not happen if length_match is true,
        // and expected_modified_chars correctly reflects expected_length.
        chars_match = false;
      }
    } else {
      chars_match =
          false; // If length doesn't match, chars can't be fully correct
    }

    if (length_match && chars_match) {
      fmt::print("Test PASSED\n\n");
      passed_count++;
    } else {
      fmt::print("Test FAILED\n\n");
    }
  }

  fmt::print("--- Test Summary ---\n");
  fmt::print("Passed: {}/{}\n", passed_count, total_tests);

  return (passed_count == total_tests) ? 0 : 1;
}
