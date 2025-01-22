package main

import (
	"fmt"
	"slices"
)

// This is a problem coming from leetcode
// https://leetcode.com/problems/3sum/description/
// Given an integer array nums, return all the triplets [nums[i], nums[j],
// nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] +
// nums[k] == 0.

// NOTE: It is accepted, but is not the efficient for some reason.
// Probably becuase of slicing arrays for each binary search. Wec an write our
// own binary search function for find some other way to implement it where
// we won't have to slice the array

func main() {
	fmt.Println(threeSum([]int{-1, 0, 1, 2, -1, -4}))
	fmt.Println(threeSum([]int{0, 1, 1}))
	fmt.Println(threeSum([]int{0, 0, 0}))
}

func threeSum(input []int) [][]int {
	slices.Sort(input)
	result := [][]int{}
	positiveIndex, _ := slices.BinarySearch(input, 1)
	positiveIndex = min(positiveIndex, len(input)-1)
	negetiveIndex, _ := slices.BinarySearch(input, 0)

	for i := 0; i <= positiveIndex; i++ {
		if i > 0 && input[i] == input[i-1] {
			continue
		}
		for j := len(input) - 1; j >= negetiveIndex && j > i+1; j-- {
			if j < len(input)-1 && input[j] == input[j+1] {
				continue
			}
			midIndex, midExists := slices.BinarySearch(input[i+1:j], -(input[j] + input[i]))
			if midExists {
				result = append(result, []int{input[i], input[i+midIndex+1], input[j]})
			}
		}
	}
	return result
}
