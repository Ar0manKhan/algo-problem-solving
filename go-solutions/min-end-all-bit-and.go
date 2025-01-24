package main

import "fmt"

// https://leetcode.com/problems/minimum-array-end/?envType=daily-question&envId=2024-11-09

func minEnd(n, x int) int64 {
	target := uint32(n - 1)
	xu := uint32(x)
	movBit := uint64(1)
	res := uint64(x)

	for target > 0 {
		xuLb := xu & 1     // xu last bit
		trLb := target & 1 // target last bit
		if xuLb == 0 {
			if trLb == 1 {
				res |= movBit
			}
			target >>= 1
		}
		xu >>= 1
		movBit <<= 1
	}

	return int64(res)
}

func main() {
	type TestCase struct {
		in, in2 int
		out     int64
	}

	testCases := []TestCase{
		{3, 4, 6},
		{2, 7, 15},
	}

	for _, tc := range testCases {
		ans := minEnd(tc.in, tc.in2)
		fmt.Println(ans == tc.out, ans, tc.out, tc.in, tc.in2)
	}
}
