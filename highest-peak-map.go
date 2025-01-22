package main

import (
	"fmt"
	"math"
	"slices"
)

// https://leetcode.com/problems/map-of-highest-peak/?envType=daily-question&envId=2025-01-22

type GridIndex struct {
	x, y int16
}

type RingBufferQueue struct {
	queue                []GridIndex
	size, maskBit, count int
	front, back          int
}

func NewRingBuffer(size int) *RingBufferQueue {
	twosSz := int(math.Pow(2, math.Ceil(math.Log2(float64(size)))))
	return &RingBufferQueue{
		queue:   make([]GridIndex, twosSz),
		size:    twosSz,
		maskBit: twosSz - 1,
	}
}

func (q *RingBufferQueue) Enquee(idx GridIndex) {
	if q.count == q.size {
		panic("queue overflow")
	}
	q.queue[q.back] = idx
	q.back = (q.back + 1) & q.maskBit
	q.count++
}

func (q *RingBufferQueue) Dequee() GridIndex {
	if q.count == 0 {
		panic("queue underflow")
	}
	res := q.queue[q.front]
	q.front = (q.front + 1) & q.maskBit
	q.count--
	return res
}

func highestPeak(isWater [][]int) [][]int {
	gridLen := len(isWater)
	rowLen := len(isWater[0])
	rb := NewRingBuffer(gridLen * rowLen)
	landGrid := make([][]int, gridLen)

	for i, row := range isWater {
		col := make([]int, rowLen)
		for j, v := range row {
			if v == 1 {
				col[j] = 0
				rb.Enquee(GridIndex{int16(i), int16(j)})
			} else {
				col[j] = -1
			}
		}
		landGrid[i] = col
	}

	neighbors := []GridIndex{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}
	for rb.count > 0 {
		idx := rb.Dequee()
		currentVal := landGrid[idx.x][idx.y]
		for _, n := range neighbors {
			nextX, nextY := idx.x+n.x, idx.y+n.y
			if nextX >= 0 && nextX < int16(gridLen) && nextY >= 0 && nextY < int16(rowLen) && landGrid[nextX][nextY] == -1 {
				landGrid[nextX][nextY] = currentVal + 1
				rb.Enquee(GridIndex{nextX, nextY})
			}
		}
	}

	return landGrid
}

func main() {
	type TestCase struct {
		isWater [][]int
		out     [][]int
	}

	testCases := []TestCase{
		{[][]int{{0, 1}, {0, 0}}, [][]int{{1, 0}, {2, 1}}},
		{[][]int{{0, 0, 1}, {1, 0, 0}, {0, 0, 0}}, [][]int{{1, 1, 0}, {0, 1, 1}, {1, 2, 2}}},
	}

	for _, tc := range testCases {
		ans := highestPeak(tc.isWater)

		for i, v := range ans {
			if !slices.Equal(v, tc.out[i]) {
				fmt.Println(false, "|", ans, "|", tc)
				break
			}
		}
		fmt.Println(true, "|", ans, "|", tc)
	}

}
