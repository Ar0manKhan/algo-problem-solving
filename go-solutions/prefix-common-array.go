package main

import (
	"fmt"
	"slices"
)

// https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/?envType=daily-question&envId=2025-01-14

/*
func findThePrefixCommonArray(A []int, B []int) []int {
	n := len(A)
	seqSum := (n*n - 1) / 2
	result := make([]int, len(A))

  for i := n-1; i > -1; i-- {

  }

  return result
}
*/

func findThePrefixCommonArray(A []int, B []int) []int {
	result := make([]int, len(A))
	aContains := make([]bool, len(A)+1)
	bContains := make([]bool, len(A)+1)

	matchedYet := 0
	for i, aVal := range A {
		bVal := B[i]
		aContains[aVal] = true
		bContains[bVal] = true

		if aContains[bVal] {
			matchedYet++
		}
		if bContains[aVal] && aVal != bVal {
			matchedYet++
		}
		result[i] = matchedYet
	}

	return result
}

func main() {
	type TestCase struct {
		A   []int
		B   []int
		out []int
	}

	testCases := []TestCase{
		{[]int{1, 3, 2, 4}, []int{3, 1, 2, 4}, []int{0, 2, 3, 4}},
		{[]int{2, 3, 1}, []int{3, 1, 2}, []int{0, 1, 3}},
	}

	for _, tc := range testCases {
		ans := findThePrefixCommonArray(tc.A, tc.B)
		fmt.Println(slices.Equal(ans, tc.out), "|", ans, "|", tc.A, tc.B, tc.out)
	}

}
