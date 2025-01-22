package main

import "fmt"

// using array for t9 mapping instead of maps
var T9_MAP = [][]string{
	{},
	{},
	{"a", "b", "c"},
	{"d", "e", "f"},
	{"g", "h", "i"},
	{"j", "k", "l"},
	{"m", "n", "o"},
	{"p", "q", "r", "s"},
	{"t", "u", "v"},
	{"w", "x", "y", "z"},
}

func main() {
	fmt.Println(letterCombinations("289"))
}

func letterCombinations(digits string) []string {
	if len(digits) == 0 {
		return []string{}
	}
	if len(digits) == 1 {
		return T9_MAP[int(digits[0]-48)]
	}
	return addCombination(int(digits[0]-48), letterCombinations(digits[1:]))
}

func addCombination(key int, prevComb []string) []string {
	res := []string{}
	for _, letter := range T9_MAP[key] {
		for _, prevWord := range prevComb {
			res = append(res, fmt.Sprintf("%s%s", letter, prevWord))
		}
	}
	return res
}
