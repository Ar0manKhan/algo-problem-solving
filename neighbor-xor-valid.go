package main

import "fmt"

// https://leetcode.com/problems/neighboring-bitwise-xor/?envType=daily-question&envId=2025-01-17

func doesValidArrayExist(derived []int) bool {
	n := int(0)

	for _, v := range derived {
		n ^= v
	}
	return n == 0
}

func main() {
	type TestCase struct {
		derived []int
		out     bool
	}

	testCases := []TestCase{
		{[]int{1, 1, 0}, true},
		{[]int{1, 1}, true},
		{[]int{1, 0}, false},
	}

	for _, tc := range testCases {
		ans := doesValidArrayExist(tc.derived)
		fmt.Println(tc.out == ans, "|", ans, "|", tc)
	}

}
