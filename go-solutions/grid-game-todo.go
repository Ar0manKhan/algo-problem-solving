package main

import (
	"fmt"
)

// https://leetcode.com/problems/grid-game/description/?envType=daily-question&envId=2025-01-21

func gridGame(grid [][]int) int64 {
	// sum row 1 & row 2
	sr1, sr2 := 0, 0
	lastVal := grid[1][len(grid[1])-1]
	for i, v := range grid[0] {
		sr1 += v
		sr2 += grid[1][i]
	}
	sr1 += lastVal
	// sr2 -= lastVal
	// copy row 1, row 2
	cr1, cr2 := sr1, sr2

	currMax := 0
	mxr1, mxr2 := 0, 0
	for i, v := range grid[0] {
		v2 := grid[1][i]
		// next sum if chosen row 1
		nr1 := 0
		// next sum if chosen row 2
		nr2 := 0
	}

	return -1
}

func main() {
	type TestCase struct {
		grid [][]int
		out  int64
	}

	testCases := []TestCase{
		{[][]int{{2, 5, 4}, {1, 5, 1}}, 4},
		{[][]int{{3, 3, 1}, {8, 5, 2}}, 4},
		{[][]int{{1, 3, 1, 15}, {1, 3, 3, 1}}, 7},
	}

	for _, tc := range testCases {
		ans := gridGame(tc.grid)
		fmt.Println(tc.out == ans, "|", ans, "|", tc)
	}

}
