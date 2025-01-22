package main

import (
	"fmt"
	"slices"
)

func maximumBeauty(items [][]int, queries []int) []int {
	// sorting and setting max beauty for each price
	slices.SortFunc(items, func(a, b []int) int {
		return (a[0] - b[0])
	})
	// setting beauty to max in all duplicate items
	pi, pe, pm := 0, items[0][0], items[0][1]
	for i, v := range items {
		if pe == v[0] {
			pm = max(pm, v[1])
			continue
		}
		for j := pi; j < i; j++ {
			items[j][1] = pm
		}
		pi = i
		pe = v[0]
		pm = v[1]
	}
	for i := pi; i < len(items); i++ {
		items[i][1] = pm
	}

	pm = 0
	for _, v := range items {
		pm = max(pm, v[1])
		v[1] = pm
	}

	// finding answer
	answer := make([]int, len(queries))
	for i, v := range queries {
		bi, found := slices.BinarySearchFunc(items, v, func(a []int, b int) int {
			return a[0] - b
		})

		if !found {
			bi--
		}

		if bi == -1 {
			continue
		}

		answer[i] = items[bi][1]
	}

	return answer
}

func main() {

	type TestCase struct {
		items   [][]int
		queries []int
		out     []int
	}

	testCases := []TestCase{
		{[][]int{{1, 2}, {3, 2}, {2, 4}, {5, 6}, {3, 5}}, []int{1, 2, 3, 4, 5, 6}, []int{2, 4, 5, 5, 6, 6}},
		{[][]int{{1, 2}, {1, 2}, {1, 3}, {1, 4}}, []int{1}, []int{4}},
		{[][]int{{10, 1000}}, []int{5}, []int{0}},
	}

	for _, tc := range testCases {
		ans := maximumBeauty(slices.Clone(tc.items), tc.queries)
		fmt.Println(slices.Equal(ans, tc.out), "|", ans, "|", tc.items, tc.queries, tc.out)
	}

	fmt.Println("hello")
}
