package main

import (
	"fmt"
	"slices"
)

// Largest Combination With Bitwise AND Greater Than Zero

func largestCombination(candidates []int) int {
	oneBitPositionCount := make([]int, 24)

	for _, v := range candidates {
		for i := 0; i < 25; i++ {
			if (v & (1 << i)) > 0 {
				oneBitPositionCount[i]++
			}
		}
	}
	return slices.Max(oneBitPositionCount)
}

func largestCombinationBitLoop24Range(candidates []int) int {
	oneBitPositionCount := make([]int, 24)

	for _, v := range candidates {
		for i := range oneBitPositionCount {
			if (v & (1 << i)) > 0 {
				oneBitPositionCount[i]++
			}
		}
	}
	return slices.Max(oneBitPositionCount)
}

func largestCombinationBitLoop24RangeI32(candidates []int) int {
	oneBitPositionCount := make([]int32, 24)

	for _, v := range candidates {
		for i := range oneBitPositionCount {
			if (v & (1 << i)) > 0 {
				oneBitPositionCount[i]++
			}
		}
	}
	return int(slices.Max(oneBitPositionCount))
}

func largestCombinationBitLoop24RangeNoIf(candidates []int) int {
	oneBitPositionCount := make([]int, 24)

	for _, v := range candidates {
		for i := range oneBitPositionCount {
			oneBitPositionCount[i] += (v & (1 << i)) >> i
		}
	}
	return slices.Max(oneBitPositionCount)
}

func largestCombinationBitLoopRangeUintNoIf(candidates []int) int {
	oneBitPositionCount := make([]uint32, 24)

	for _, v := range candidates {
		for i := range oneBitPositionCount {
			oneBitPositionCount[i] += uint32((v & (1 << i)) >> i)
		}
	}
	return int(slices.Max(oneBitPositionCount))
}

// AI suggested unrolling the loop and >> directly
func largestCombinationBitUnroll(candidates []int) int {
	counts := make([]uint32, 24)

	for _, v := range candidates {
		num := uint32(v)
		counts[0] += num & 1
		counts[1] += (num >> 1) & 1
		counts[2] += (num >> 2) & 1
		counts[3] += (num >> 3) & 1
		counts[4] += (num >> 4) & 1
		counts[5] += (num >> 5) & 1
		counts[6] += (num >> 6) & 1
		counts[7] += (num >> 7) & 1
		counts[8] += (num >> 8) & 1
		counts[9] += (num >> 9) & 1
		counts[10] += (num >> 10) & 1
		counts[11] += (num >> 11) & 1
		counts[12] += (num >> 12) & 1
		counts[13] += (num >> 13) & 1
		counts[14] += (num >> 14) & 1
		counts[15] += (num >> 15) & 1
		counts[16] += (num >> 16) & 1
		counts[17] += (num >> 17) & 1
		counts[18] += (num >> 18) & 1
		counts[19] += (num >> 19) & 1
		counts[20] += (num >> 20) & 1
		counts[21] += (num >> 21) & 1
		counts[22] += (num >> 22) & 1
		counts[23] += (num >> 23) & 1
	}
	return int(slices.Max(counts))
}

func main() {
	type TestCase struct {
		in  []int
		out int
	}

	testCase := []TestCase{
		{[]int{16, 17, 71, 62, 12, 24, 14}, 4},
		{[]int{8, 8}, 2},
		{[]int{16, 16, 48, 71, 62, 12, 24, 14, 17, 18, 19, 20, 10000}, 10},
	}

	for _, v := range testCase {
		res := largestCombination(v.in)
		fmt.Println(res == v.out, res, v.out, v.in)
	}
}
