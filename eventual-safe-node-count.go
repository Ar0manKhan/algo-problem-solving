package main

import (
	"fmt"
	"slices"
)

// https://leetcode.com/problems/find-eventual-safe-states/description/?envType=daily-question&envId=2025-01-24

func eventualSafeNodes(graph [][]int) []int {
	// reverse graph
	revGraph := make([][]uint16, len(graph))
	stack := []uint16{}

	for i, row := range graph {
		for _, v := range row {
			revGraph[v] = append(revGraph[v], uint16(i))
		}
	}

	unsafeCount := make([]uint16, len(graph))
	for i, v := range graph {
		neighbors := uint16(len(v))
		unsafeCount[i] = neighbors
		if neighbors == 0 {
			stack = append(stack, uint16(i))
		}
	}

	// going thbrough each item in stack and marking for potentinal safe nodes
	for len(stack) > 0 {
		safeNode := stack[len(stack)-1]
		stack = stack[:len(stack)-1]

		for _, v := range revGraph[safeNode] {
			unsafeCount[v]--
			if unsafeCount[v] == 0 {
				stack = append(stack, v)
			}
		}
	}

	result := []int{}
	for i, v := range unsafeCount {
		if v == 0 {
			result = append(result, i)
		}
	}
	return result
}

func main() {
	type TestCase struct {
		graph [][]int
		out   []int
	}

	testCases := []TestCase{
		{[][]int{{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}}, []int{2, 4, 5, 6}},
		{[][]int{{1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {}}, []int{4}},
	}

	for _, tc := range testCases {
		ans := eventualSafeNodes(tc.graph)
		fmt.Println(slices.Equal(ans, tc.out), "|", ans, "|", tc)
	}

}
