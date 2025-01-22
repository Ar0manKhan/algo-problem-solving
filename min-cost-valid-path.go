package main

import (
	"container/heap"
	"fmt"
	"math"
	"slices"
)

// https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/description/?envType=daily-question&envId=2025-01-18

type Cords struct{ x, y int }

type Item struct {
	cell Cords
	cost uint8
}

type costQueue []Item

func (piq costQueue) Len() int {
	return len(piq)
}
func (piq costQueue) Less(i, j int) bool {

	return piq[i].cost < piq[j].cost
}
func (piq costQueue) Swap(i, j int) {
	piq[i], piq[j] = piq[j], piq[i]
}
func (piq *costQueue) Push(x interface{}) {
	item := x.(Item)
	*piq = append(*piq, item)
}
func (piq *costQueue) Pop() interface{} {
	old := *piq
	n := len(old)
	item := old[n-1]
	*piq = old[0 : n-1]
	return item
}

func isValidCell(curr, limit Cords) bool {
	return curr.x >= 0 && curr.y >= 0 && curr.x < limit.x && curr.y < limit.y
}

func minCost(grid [][]int) int {
	moveGrid := []Cords{Cords{0, 1}, Cords{0, -1}, Cords{1, 0}, Cords{-1, 0}}
	limit := Cords{len(grid), len(grid[0])}
	// cost from start grid
	costGrid := make([][]uint8, limit.x)
	for i := range grid {
		costGrid[i] = slices.Repeat([]uint8{math.MaxUint8}, limit.y)
	}
	costGrid[0][0] = 0
	// cost queue
	piq := make(costQueue, 0)
	// pushing all directions from 0,0
	for i, v := range moveGrid {
		cd := grid[0][0] - 1
		if !isValidCell(v, limit) {
			continue
		}
		if cd == i {
			heap.Push(&piq, Item{v, 0})
		} else {
			heap.Push(&piq, Item{v, 1})
		}
	}
	target := Cords{limit.x - 1, limit.y - 1}
	for len(piq) > 0 {
		c := heap.Pop(&piq).(Item)
		cell := c.cell
		if cell == target {
			return int(c.cost)
		}
		if costGrid[cell.x][cell.y] != math.MaxUint8 {
			continue
		}
		costGrid[cell.x][cell.y] = c.cost
		for i, v := range moveGrid {
			next := Cords{cell.x + v.x, cell.y + v.y}
			if !isValidCell(next, limit) {
				continue
			}
			cd := grid[cell.x][cell.y] - 1
			if cd == i {
				heap.Push(&piq, Item{next, c.cost})
			} else {
				heap.Push(&piq, Item{next, c.cost + 1})
			}
		}

	}
	return int(costGrid[target.x][target.y])
}

func main() {
	type TestCase struct {
		grid [][]int
		out  int
	}

	testCases := []TestCase{
		{[][]int{{1, 1, 1, 1}, {2, 2, 2, 2}, {1, 1, 1, 1}, {2, 2, 2, 2}}, 3},
		{[][]int{{1, 1, 3}, {3, 2, 2}, {1, 1, 4}}, 0},
		{[][]int{{1, 2}, {4, 3}}, 1},
		{[][]int{{4}}, 0},
	}

	for _, tc := range testCases {
		ans := minCost(tc.grid)
		fmt.Println(tc.out == ans, "|", ans, "|", tc)
	}

}
