package main

import (
	"fmt"
)

func shortestSubarray(nums []int, k int) int {
	// could have been solved by monotonic dequeu, but i don't know that theory
	return -1
}

func main() {
	type TestCase struct {
		nums   []int
		k, out int
	}

	testCases := []TestCase{
		{[]int{1}, 1, 1},
		{[]int{1, 2}, 4, -1},
		{[]int{2, -1, 2}, 3, 3},
	}

	for _, tc := range testCases {
		ans := shortestSubarray(tc.nums, tc.k)
		fmt.Println(ans == tc.out, "|", ans, tc.out, "|", tc.nums, tc.k)
	}
}
