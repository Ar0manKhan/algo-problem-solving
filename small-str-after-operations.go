package main

import "fmt"

// https://leetcode.com/problems/minimum-length-of-string-after-operations/description/?envType=daily-question&envId=2025-01-13

func minimumLength(s string) int {
	charCount := make([]uint32, 26)

	for _, v := range s {
		charCount[v-'a']++
	}

	result := uint32(0)

	for _, v := range charCount {
		if v > 0 {
			if v&1 == 0 {
				result += 2
			} else {
				result++
			}
		}
	}

	return int(result)
}

func main() {
	type TestCase struct {
		in  string
		out int
	}

	testCases := []TestCase{
		{"abaacbcbb", 5},
		{"aa", 2},
		{"ucvbutgkohgbcobqeyqwppbxqoynxeuuzouyvmydfhrprdbuzwqebwuiejoxsxdhbmuaiscalnteocghnlisxxawxgcjloevrdcj", 38},
	}

	for _, tc := range testCases {
		ans := minimumLength(tc.in)
		fmt.Println(tc.out == ans, "|", ans, "|", tc.in, tc.out)
	}

}
