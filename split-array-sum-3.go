package main

/*
* Question: The array nums contains n non-negetive integers. Determine the
* number of ways to split nums into three non-empty sybarrays A1, A2, and A3
* with the sum of elements of the subarrays as S1, S2, and S3 respectively,
* such that S1, S3, and S3 satisfy S2 <= S1 + S3.
* Return the value modulo (10^9+7)
*
* Constrains:
* 3 <= n <= 10^5
* 0 <= nums[i] <= 10^6
 */

import (
	"fmt"
)

func main() {
	x := []int{1, 2, 3, 4, 5}
	fmt.Println(CountWays(x))
	// TestSplitArrayIn3()
}

func CountWays(src []int) int {
	// Generating sum ladder
	sumLadder := make([]int, len(src))
	cs := 0
	for i, v := range src {
		cs += v
		sumLadder[i] = cs
	}

	totalWays := 0
	fmt.Println(sumLadder)

	for i := range sumLadder {
		if i == len(sumLadder)-1 {
			break
		}
		// fmt.Println(i, v, findIndex(sumLadder, i))
		finalIdx := findIndex(sumLadder, i)
		if finalIdx < i {
			continue
		}
		// println(i, v, sumLadder[finalIdx], finalIdx)
		totalWays += finalIdx - i + 1
	}

	return totalWays
}

func findIndex(sumLadder []int, idx int) int {
	finalSum := sumLadder[len(sumLadder)-1]
	a := sumLadder[idx]

	for i := len(sumLadder) - 2; i > idx; i-- {
		c := finalSum - sumLadder[i]
		b := sumLadder[i] - a
		if b <= a+c {
			return i
		}
	}

	return idx
}

func TestSplitArrayIn3() {
	testCases := []struct {
		input  []int
		answer int
	}{
		{[]int{1, 2, 3, 4, 5}, 3},
		{[]int{1, 2, 3}, 1},
		{[]int{1, 1, 1, 2, 2, 2}, 6},
	}

	for _, t := range testCases {
		fmt.Println(t.input, CountWays(t.input), t.answer)
	}
}
