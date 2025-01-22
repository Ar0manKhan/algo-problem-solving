package main

import (
	"fmt"
	"slices"
)

func resultsArray(nums []int, k int) []int {
	k--
	result := make([]int, len(nums)-k)

	s := 0  // total sum
	ps := 0 // previous sum
	for i := 0; i < k; i++ {
		s += nums[i]
	}

	for i := k; i < len(nums); i++ {
		s += nums[i]
		// fmt.Println(i, s, ps, nums[i], consecutiveSum(nums[i]), nums[i-k], consecutiveSum(nums[i-k]-1))
		if (s - ps) == (consecutiveSum(nums[i]) - consecutiveSum(nums[i-k]-1)) {
			result[i-k] = nums[i]
		} else {
			result[i-k] = -1
		}
		ps += nums[i-k]
	}
	return result
}

func consecutiveSum(n int) int {
	return (n * (n + 1)) >> 1
}

func main() {
	type TestCase struct {
		nums []int
		k    int
		out  []int
	}

	testCases := []TestCase{
		{[]int{1, 2, 3, 4, 3, 2, 5}, 3, []int{3, 4, -1, -1, -1}},
		{[]int{2, 2, 2, 2, 2}, 4, []int{-1, -1}},
		{[]int{3, 2, 3, 2, 3, 2}, 2, []int{-1, 3, -1, 3, -1}},
	}

	for _, v := range testCases {
		ans := resultsArray(v.nums, v.k)
		fmt.Printf("%v | %v %v | %v %v\n", slices.Equal(v.out, ans), ans, v.out, v.nums, v.k)
	}
}
