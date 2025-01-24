package main

import (
	"fmt"
	"slices"
)

// https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/description/?envType=daily-question&envId=2024-11-14

func minimizedMaximum(n int, quantities []int) int {
	start, end := 1, slices.Max(quantities)
	mid := start + (end-start)/2
	res := 1

	for start <= end {
		mid = start + (end-start)/2
		slotsFilled := 0
		for _, v := range quantities {
			slotsFilled += v / mid
			if v%int(mid) > 0 {
				slotsFilled++
			}
		}
		// fmt.Printf("for start: %d, mid: %d, end: %d, slots filled: %d\n", start, mid, end, slotsFilled)

		if slotsFilled > n {
			start = mid + 1
		} else {
			res = mid
			end = mid - 1
		}
	}
	return res
}

func main() {
	type TestCase struct {
		n          int
		quantities []int
		out        int
	}

	testCases := []TestCase{
		{22, []int{25, 11, 29, 6, 24, 4, 29, 18, 6, 13, 25, 30}, 13},
		{4, []int{7, 5, 1}, 5},
		{3, []int{7, 5}, 5},
		{6, []int{11, 6}, 3},
		{7, []int{15, 10, 10}, 5},
		{1, []int{100000}, 100000},
	}

	for _, tc := range testCases {
		qt := slices.Clone(tc.quantities)
		ans := minimizedMaximum(tc.n, qt)
		fmt.Println(tc.out == ans, "|", ans, tc.out, "|", tc.n, tc.quantities)
	}
}
