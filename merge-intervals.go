package main

import (
	"cmp"
	"fmt"
	"slices"
)

type Interval []int
type IntervalSet []Interval

func main() {
	intervals := IntervalSet{
		Interval{2, 5},
		Interval{1, 4},
		Interval{7, 9},
	}
	fmt.Println(intervals.MergeIntervals())
}

func (intervals IntervalSet) MergeIntervals() IntervalSet {
	if len(intervals) < 2 {
		return intervals
	}
	// sorting the intervals
	slices.SortFunc(intervals, func(a, b Interval) int {
		return cmp.Compare(a[0], b[0])
	})
	result := IntervalSet{}

	x := intervals[0]
	for _, i := range intervals[1:] {
		if x[1] > i[0] {
			x[1] = max(x[1], i[1])
		} else {
			result = append(result, x)
			x = i
		}
	}
	result = append(result, x)
	return result
}
