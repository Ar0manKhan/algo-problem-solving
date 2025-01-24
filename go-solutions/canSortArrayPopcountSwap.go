package main

import (
	"fmt"
	"math/bits"
)

// https://leetcode.com/problems/find-if-array-can-be-sorted/description/?envType=daily-question&envId=2024-11-06

/*
* v1 - wrong, due to bad understanding of question
func canSortArray(nums []int) bool {
	bcNumsPre := make([]int8, len(nums))
	for i, v := range nums {
		bcNumsPre[i] = int8(bits.OnesCount16(uint16(v)))
	}
	fmt.Println(bcNumsPre)
	slices.Sort(nums)
	for i, v := range nums {
		fmt.Println(int8(bits.OnesCount16(uint16(v))))
		if bcNumsPre[i] != int8(bits.OnesCount16(uint16(v))) {
			return false
		}
	}
	return true
}
*/

func canSortArray(nums []int) bool {
	if len(nums) == 1 {
		return true
	}

	prevBc := bits.OnesCount16(uint16(nums[0])) // Previous Set bit count
	prevBcLargest := 0
	largestElemYet := nums[0]

	for _, v := range nums[1:] {
		bc := bits.OnesCount16(uint16(v))

		if bc != prevBc {
			if largestElemYet > v {
				return false
			}
			prevBc = bc
			prevBcLargest = largestElemYet
			largestElemYet = v
		} else {
			if prevBcLargest > v {
				return false
			}
			largestElemYet = max(largestElemYet, v)
		}
	}

	return true
}

func main() {
	type TestCase struct {
		in  []int
		out bool
	}

	testCase := []TestCase{
		{[]int{8, 4, 2, 30, 15}, true},
		{[]int{1, 2, 3, 4, 5}, true},
		{[]int{3, 16, 8, 4, 2}, false},
		{[]int{75, 34, 30}, false},
	}

	for _, tc := range testCase {
		fmt.Println(tc.in, tc.out, canSortArray(tc.in) == tc.out)
	}
}

/*
define largestElemYet

case 1: only 1 element
  return true at the top of fn
case 2: adjecent has same pop bits
  set largestElemYet to max(prevElement, currentElement)
case 3: adjcent has different pop bits
case 3a: prev element is smaller
  set largestElemYet to current element
  continue
case 3b: prev element is larger
  return false
case 3b:

*/
