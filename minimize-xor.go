package main

import (
	"fmt"
	"math/bits"
)

// https://leetcode.com/problems/minimize-xor/?envType=daily-question&envId=2025-01-15

func minimizeXor(num1 int, num2 int) int {

	extraBits := bits.OnesCount(uint(num2))
	result := 0

	for i := 29; i > -1 && i >= extraBits && extraBits > 0; i-- {
		x := 1 << i
		if num1&x > 0 {
			result |= x
			extraBits--
		}
	}

	for i := 0; i < extraBits; i++ {
		result |= (1 << i)
	}

	return result
}

func main() {
	type TestCase struct {
		num1, num2, out int
	}

	testCases := []TestCase{
		{3, 5, 3},
		{1, 12, 3},
	}

	for _, tc := range testCases {
		ans := minimizeXor(tc.num1, tc.num2)
		fmt.Println(ans == tc.out, "|", ans, "|", tc)
	}

}
