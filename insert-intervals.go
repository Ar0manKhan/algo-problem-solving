package main

import (
	"cmp"
	"fmt"
	"slices"
)

func main() {
	intervals := [][]int{
		{1, 3},
		{6, 9},
	}

	fmt.Println(InsertIntervals(intervals, []int{2, 5}))
}

func InsertIntervals(intervals [][]int, newInterval []int) [][]int {
	slices.SortFunc(intervals, func(a, b []int) int {
		return cmp.Compare(a[0], b[0])
	})
	fmt.Println(intervals)
	result := [][]int{}

	leftIdx, _ := slices.BinarySearchFunc(intervals, newInterval[0], func(a []int, b int) int {
		return cmp.Compare(a[0], b)
	})

	if leftIdx > 0 {
		result = append(result, intervals[:leftIdx]...)
	}

	lastIdx, _ := slices.BinarySearchFunc(intervals, newInterval, func(a, b []int) int {
		return cmp.Compare(a[1], b[1])
	})

	// case 1 - last index starts with bigger val
	// case 2 - last index does not

	if lastIdx < len(intervals) {
		if intervals[lastIdx][0] > newInterval[1] {
			// appned new new index with handling middle part
			if lastIdx != 0 {
				newInterval[1] = max(newInterval[1], intervals[lastIdx-1][1])
			}
			result = append(result, newInterval)
			result = append(result, intervals[lastIdx:]...)
		} else {
			newInterval[1] = max(intervals[lastIdx][1], newInterval[1])
			result = append(result, newInterval)
			result = append(result, intervals[lastIdx+1:]...)
		}
	} else {
		// just append the new interval
		result = append(result, newInterval)
	}

	return result
}

/*
func InsertIntervals(intervals [][]int, newInterval []int) [][]int {
	slices.SortFunc(intervals, func(a, b []int) int {
		return cmp.Compare(a[0], b[0])
	})
	fmt.Println(intervals)
	result := [][]int{}

	firstIdx, _ := slices.BinarySearchFunc(intervals, newInterval, func(a, b []int) int {
		return cmp.Compare(a[0], b[0])
	})

	if firstIdx > 0 {
		result = append(result, intervals[:firstIdx]...)
	}

	lastIdx, _ := slices.BinarySearchFunc(intervals, newInterval, func(a, b []int) int {
		return cmp.Compare(a[1], b[1])
	})

	// case 1 - last index starts with bigger val
	// case 2 - last index does not

	if lastIdx < len(intervals) {
		if intervals[lastIdx][0] > newInterval[1] {
			// appned new new index with handling middle part
			if lastIdx != 0 {
				newInterval[1] = max(newInterval[1], intervals[lastIdx-1][1])
			}
			result = append(result, newInterval)
			result = append(result, intervals[lastIdx:]...)
		} else {
			newInterval[1] = max(intervals[lastIdx][1], newInterval[1])
			result = append(result, newInterval)
			result = append(result, intervals[lastIdx+1:]...)
		}
	} else {
		// just append the new interval
		result = append(result, newInterval)
	}

	return result
}
*/
