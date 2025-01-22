package main

import "fmt"

// https://leetcode.com/problems/bitwise-xor-of-all-pairings/description/?envType=daily-question&envId=2025-01-16

func xorAllNums(nums1 []int, nums2 []int) int {
	a, b := 0, 0

	for _, v := range nums1 {
		a ^= v
	}
	for _, v := range nums2 {
		b ^= v
	}
	return ((len(nums1) & 1) * b) ^ ((len(nums2) & 1) * a)
}

func main() {
	type TestCase struct {
		num1, num2 []int
		out        int
	}

	testCases := []TestCase{
		{[]int{2, 1, 3}, []int{10, 2, 5, 0}, 13},
		{[]int{1, 2}, []int{3, 4}, 0},
	}

	for _, tc := range testCases {
		ans := xorAllNums(tc.num1, tc.num2)
		fmt.Println(tc.out == ans, "|", ans, "|", tc)
	}

}
