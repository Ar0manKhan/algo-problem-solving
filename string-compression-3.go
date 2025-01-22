package main

import (
	"fmt"
	"strings"
)

// v3
func StringCompression3(word string) string {
	// resultBytes := []rune{}
	// resultCounts := []uint8{}

	var sb strings.Builder

	prevCount := 1
	prevLetter := rune(word[0])

	for _, l := range word[1:] {
		if prevCount < 9 && prevLetter == l {
			prevCount++
			continue
		}

		sb.WriteRune('0' + rune(prevCount))
		sb.WriteRune(prevLetter)

		prevCount = 1
		prevLetter = l
	}

	sb.WriteRune('0' + rune(prevCount))
	sb.WriteRune(prevLetter)

	return sb.String()
}

/*
// v2
func StringCompression3(word string) string {
	resultBytes := []rune{}
	resultCounts := []int{}

	prevCount := int(1)
	prevLetter := rune(word[0])

	for _, l := range word[1:] {

		if prevLetter == l {
			prevCount++
			continue
		}

		resultBytes = append(resultBytes, prevLetter)
		resultCounts = append(resultCounts, prevCount)

		prevCount = 1
		prevLetter = l
	}

	resultBytes = append(resultBytes, prevLetter)
	resultCounts = append(resultCounts, prevCount)

	var sb strings.Builder
	sb.Grow(len(resultBytes) * 2)

	for i, v := range resultCounts {
		for v > 0 {
			sb.WriteRune(rune('0') + rune(min(v, 9)))
			v -= 9
			sb.WriteRune(resultBytes[i])
		}
	}
	return sb.String()
}
*/

/*
// v1
func StringCompression3(word string) string {
	resultBytes := []rune{}
	resultCounts := []uint8{}

	prevCount := uint8(1)
	prevLetter := rune(word[0])

	for _, l := range word[1:] {
		if prevCount < 9 && prevLetter == l {
			prevCount++
			continue
		}

		resultBytes = append(resultBytes, prevLetter)
		resultCounts = append(resultCounts, prevCount)

		prevCount = 1
		prevLetter = l
	}

	resultBytes = append(resultBytes, prevLetter)
	resultCounts = append(resultCounts, prevCount)

	var sb strings.Builder
	sb.Grow(len(resultBytes) * 2)

	for i, v := range resultBytes {
		sb.WriteRune(rune('0') + rune(resultCounts[i]))
		sb.WriteRune(v)
	}
	return sb.String()
}
*/

func main() {
	fmt.Println("abcde", "1a1b1c1d1e", StringCompression3("abcde"), "1a1b1c1d1e" == StringCompression3("abcde"))
	fmt.Println("aaaaaaaaaaaaaabb", "9a5a2b", StringCompression3("aaaaaaaaaaaaaabb"), "9a5a2b" == StringCompression3("aaaaaaaaaaaaaabb"))
}
