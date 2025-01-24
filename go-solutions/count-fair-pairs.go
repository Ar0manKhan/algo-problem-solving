package main

// Count the Number of Fair Pairs
// https://leetcode.com/problems/count-the-number-of-fair-pairs/description/?envType=daily-question&envId=2024-11-13

import (
	"fmt"
	"slices"
)

// TODO: count pairs should count lower  and upper pair count seperately
// then do upper - lower
func countFairPairs(nums []int, lower int, upper int) int64 {
	slices.Sort(nums)

	// fmt.Println(nums)

	res := int64(0)

	start := len(nums) - 1
	end := start
	j := end

	for i, v := range nums {
		for j = end; j > i && nums[j]+v > upper; j-- {
		}
		end = max(j, i)
		for j = min(j, start); j > i && nums[j]+v >= lower; j-- {
		}
		start = max(j, i)
		res += int64(end - start)
	}

	return res
}

func main() {
	type TestCase struct {
		nums         []int
		lower, upper int
		out          int64
	}

	testCases := []TestCase{
		{[]int{0, 1, 7, 4, 4, 5}, 3, 6, 6},
		{[]int{1, 7, 9, 2, 5}, 11, 11, 1},
		{[]int{0, 0, 0, 0, 0, 0}, 0, 0, 15},
	}

	for _, tc := range testCases {
		nums := slices.Clone(tc.nums)
		ans := countFairPairs(tc.nums, tc.lower, tc.upper)
		fmt.Println(ans == tc.out, "|", ans, tc.out, "|", nums, tc.lower, tc.upper)
	}
}
