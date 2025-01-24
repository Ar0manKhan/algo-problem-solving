package main

import "fmt"

func minimumSubarrayLength(nums []int, k int) int {
	if k == 0 {
		return 1
	}
	res := len(nums) + 1
	curRes := 0
	for i, v := range nums {
		// fmt.Println("for:", i, v)
		curRes |= v

		if curRes < k {
			continue
		}

		// loop back from i to max(i-res, )
		curRes = 0
		prevRes := 0
		j := i
		for ; j > (i-res) && curRes < k; j-- {
			prevRes = curRes
			curRes |= nums[j]
		}

		if curRes < k {
			continue
		}

		// fmt.Println(j, res)
		res = min(i-j, res)
		curRes = prevRes
	}

	if res == len(nums)+1 {
		return -1
	}
	return res
}

func main() {
	type TestCase struct {
		nums []int
		k    int
		out  int
	}

	testCases := []TestCase{
		{[]int{1, 2, 3}, 2, 1},
		{[]int{2, 1, 8}, 10, 3},
		{[]int{1, 2}, 0, 1},
		{[]int{2, 1, 9, 12}, 21, -1},
	}

	for _, tc := range testCases {
		ans := minimumSubarrayLength(tc.nums, tc.k)
		fmt.Println(ans == tc.out, ans, tc.out, tc.nums, tc.k)
	}
}
