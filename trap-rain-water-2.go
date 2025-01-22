package main

import "fmt"

// https://leetcode.com/problems/trapping-rain-water-ii/?envType=daily-question&envId=2025-01-19

type Direction struct {
	up, right, down, left uint16
}

func trapRainWater(heightMap [][]int) int {
	x, y := len(heightMap), len(heightMap[0])
	boundaries := make([][]Direction, x)
	for i := range boundaries {
		boundaries[i] = make([]Direction, y)
	}
	// populating left to right boundaries
	for i, r := range heightMap {
		mx := 0
		for j, v := range r {
			mx = max(mx, v)
			boundaries[i][j].left = uint16(mx)
		}
	}
	// populating right to left boundaries
	for i, r := range heightMap {
		mx := 0
		for j := y - 1; j > -1; j-- {
			v := r[j]
			mx = max(mx, v)
			boundaries[i][j].right = uint16(mx)
		}
	}
	// populating up to down
	for j := 0; j < y; j++ {
		mx := 0
		for i := 0; i < x; i++ {
			v := heightMap[i][j]
			mx = max(mx, v)
			boundaries[i][j].up = uint16(mx)
		}
	}
	// populating down to up
	for j := 0; j < y; j++ {
		mx := 0
		for i := x - 1; i > -1; i-- {
			v := heightMap[i][j]
			mx = max(mx, v)
			boundaries[i][j].down = uint16(mx)
		}
	}

	fmt.Println("boundaries")
	for _, r := range boundaries {
		fmt.Println(r)
	}

	result := uint(0)
	for i, r := range heightMap {
		for j, v := range r {
			b := boundaries[i][j]
			w := uint16(v)
			result += uint(min(b.up-w, b.right-w, b.down-w, b.left-w))
		}
	}

	return int(result)
}

func main() {
	type TestCase struct {
		heightMap [][]int
		out       int
	}

	testCases := []TestCase{
		// {[][]int{{1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}}, 4},
		// {[][]int{{3, 3, 3, 3, 3}, {3, 2, 2, 2, 3}, {3, 2, 1, 2, 3}, {3, 2, 2, 2, 3}, {3, 3, 3, 3, 3}}, 10},
		{[][]int{{12, 13, 1, 12}, {13, 4, 13, 12}, {13, 8, 10, 12}, {12, 13, 12, 12}, {13, 13, 13, 13}}, 14},
	}

	for _, tc := range testCases {
		ans := trapRainWater(tc.heightMap)
		fmt.Println(ans == tc.out, "|", ans, "|", tc)
	}

}

/*
*
*
	fmt.Println("boundaries")
	for _, r := range boundaries {
		fmt.Println(r)
	}
*/
