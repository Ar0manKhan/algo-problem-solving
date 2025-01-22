package main

import "fmt"

// leetcode - 2914. Minimum Number of Changes to Make Binary String Beautiful

func minChanges(s string) int {
	n := len(s)
	r := 0

	for i := 0; i < n; i += 2 {
		if s[i] != s[i+1] {
			r++
		}
	}
	return r
}

func main() {
	type TestStruct struct {
		in  string
		out int
	}
	testData := []TestStruct{
		TestStruct{"1001", 2},
		TestStruct{"10", 1},
		TestStruct{"0000", 0},
	}
	for _, test := range testData {
		fmt.Println(test.in, test.out, minChanges(test.in) == test.out)
	}
}
