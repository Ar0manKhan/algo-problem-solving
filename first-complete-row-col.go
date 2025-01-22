package main

import (
	"fmt"
	"slices"
)

// https://leetcode.com/problems/first-completely-painted-row-or-column/description/?envType=daily-question&envId=2025-01-20

func firstCompleteIndex(arr []int, mat [][]int) int {
	minIdxFound := slices.Repeat([]int{len(arr) + 1}, len(arr)+1)
	for i, v := range arr {
		minIdxFound[v] = min(i, minIdxFound[v])
	}

	// fmt.Println("Min mapping", minIdxFound)

	result := len(arr) + 1

	// checking row-wise
	for _, r := range mat {
		currMax := -1
		for _, v := range r {
			currMax = max(minIdxFound[v], currMax)
		}
		result = min(currMax, result)
	}

	// checking column wise
	for j := 0; j < len(mat[0]); j++ {
		currMax := -1
		for i := 0; i < len(mat); i++ {
			currMax = max(minIdxFound[mat[i][j]], currMax)
		}
		result = min(currMax, result)
	}

	return result
}

func main() {
	type TestCase struct {
		arr []int
		mat [][]int
		out int
	}

	testCases := []TestCase{
		{[]int{1, 3, 4, 2}, [][]int{{1, 4}, {2, 3}}, 2},
		{[]int{2, 8, 7, 4, 1, 3, 5, 6, 9}, [][]int{{3, 2, 5}, {1, 4, 6}, {8, 7, 9}}, 3},
	}

	for _, tc := range testCases {
		ans := firstCompleteIndex(tc.arr, tc.mat)
		fmt.Println(ans == tc.out, "|", ans, "|", tc)
	}

}
