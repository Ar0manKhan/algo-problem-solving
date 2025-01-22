package main

import (
	"fmt"
	"slices"
)

// leetcode - https://leetcode.com/problems/maximum-xor-for-each-query/?envType=daily-question&envId=2024-11-08

func getMaximumXor(nums []int, maximumBit int) []int {
	resXor := uint32((1 << maximumBit) - 1)
	currXor := uint32(0)

	n := len(nums)
	res := make([]int, n)

	for i, v := range nums {
		currXor ^= uint32(v)
		res[i] = int(resXor ^ currXor)
	}
	slices.Reverse(res)
	return res
}

func main() {
	type TestCase struct {
		in  []int
		in2 int
		out []int
	}

	testCases := []TestCase{
		{[]int{0, 1, 1, 3}, 2, []int{0, 3, 2, 3}},
		{[]int{2, 3, 4, 7}, 3, []int{5, 2, 6, 5}},
		{[]int{0, 1, 2, 2, 5, 7}, 3, []int{4, 3, 6, 4, 6, 7}},
	}

	for _, tc := range testCases {
		ans := getMaximumXor(tc.in, tc.in2)
		fmt.Println(slices.Equal(ans, tc.out), ans, tc.out, tc.in, tc.in2)
	}
}
