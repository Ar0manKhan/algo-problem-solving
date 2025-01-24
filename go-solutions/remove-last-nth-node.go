package main

func main() {
	a := &ListNode{2, nil}
	b := &ListNode{43, a}
	c := &ListNode{22, b}
	d := &ListNode{99, c}
	e := &ListNode{111, d}

	res := removeNthFromEnd(e, 10)
	res.Display()
}

type ListNode struct {
	Val  int
	Next *ListNode
}

func removeNthFromEnd(head *ListNode, n int) *ListNode {
	temp := head
	targetNode := head
	targetCount := 0
	for temp != nil {
		if targetCount == n+1 {
			targetNode = targetNode.Next
		} else {
			targetCount++
		}
		temp = temp.Next
	}
	if targetCount < n+1 {
		return head.Next
	}
	targetNode.Next = targetNode.Next.Next
	return head
}

func (n *ListNode) Display() {
	if n == nil {
		return
	}

	temp := n
	for temp != nil {
		print(temp.Val, " -> ")
		temp = temp.Next
	}
}
