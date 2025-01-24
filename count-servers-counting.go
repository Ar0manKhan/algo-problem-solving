package main

import "fmt"

// https://leetcode.com/problems/count-servers-that-communicate/description/?envType=daily-question&envId=2025-01-23

func countServers(grid [][]int) int {
	rowContains := make([]uint8, len(grid))
	colContains := make([]uint8, len(grid[0]))
	result := 0
	for i, row := range grid {
		rowCount := 0
		for j, v := range row {
			rowCount += v
			colContains[j] += uint8(v)
		}
		rowContains[i] = uint8(rowCount)
	}
	for i, row := range grid {
		for j, v := range row {
			if v == 1 && (rowContains[i] > 1 || colContains[j] > 1) {
				result++
			}
		}
	}
	return result
}

func main() {
	type TestCase struct {
		grid [][]int
		out  int
	}

	testCases := []TestCase{
		{[][]int{{1, 0}, {0, 1}}, 0},
		{[][]int{{1, 0}, {1, 1}}, 3},
		{[][]int{{1, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}, 4},
	}

	for _, tc := range testCases {
		ans := countServers(tc.grid)
		fmt.Println(tc.out == ans, "|", ans, "|", tc)
	}

}
