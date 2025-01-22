package main

import (
	"fmt"
	"strings"
)

// leetcode.com/problems/adding-spaces-to-a-string/

/*
func addSpaces(s string, spaces []int) string {
	var sb strings.Builder
	sb.Grow(len(s) + len(spaces))

	prevIdx := 0
	for _, v := range spaces {
		for ; prevIdx < v; prevIdx++ {
			sb.WriteByte(s[prevIdx])
		}
		sb.WriteByte(' ')
	}
	sb.WriteString(s[prevIdx:])

	return sb.String()
}
*/

func addSpaces(s string, spaces []int) string {
	var sb strings.Builder
	sb.Grow(len(s) + len(spaces))

	prevIdx := 0
	for _, v := range spaces {
		sb.WriteString(s[prevIdx:v])
		sb.WriteByte(' ')
		prevIdx = v
	}
	sb.WriteString(s[prevIdx:])

	return sb.String()
}

func main() {
	type TestCase struct {
		s      string
		spaces []int
		out    string
	}

	testCases := []TestCase{
		{"LeetcodeHelpsMeLearn", []int{8, 13, 15}, "Leetcode Helps Me Learn"},
		{"icodeinpython", []int{1, 5, 7, 9}, "i code in py thon"},
		{"spacing", []int{0, 1, 2, 3, 4, 5, 6}, " s p a c i n g"},
	}

	for _, tc := range testCases {
		ans := addSpaces(tc.s, tc.spaces)
		fmt.Println(ans == tc.out, "|", ans, "|", tc)
	}

}
