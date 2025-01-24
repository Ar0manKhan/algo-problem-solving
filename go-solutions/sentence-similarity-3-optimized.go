package main

func SentenceSimilarity3(sentence1, sentence2 string) bool {
	// Early length check to avoid unnecessary processing
	len1, len2 := len(sentence1), len(sentence2)

	minLen := len1
	if len2 < len1 {
		minLen = len2
	}

	// Preallocate these values
	lsp := -1
	i := 0

	// Use a single loop to find both lsp and first difference
	for ; i < minLen && sentence1[i] == sentence2[i]; i++ {
		if sentence1[i] == ' ' {
			lsp = i
		}
	}

	// Check if we reached the end of the shorter string
	if i == minLen &&
		((len1 == len2) ||
			(len1 > minLen && sentence1[i] == ' ') ||
			(len2 > minLen && sentence2[i] == ' ')) {
		return true
	}

	// If we're here, the strings differ before minLen
	target := minLen - lsp

	// Use array indexing instead of len() in the loop
	s1end := len1 - 1
	s2end := len2 - 1

	for j := 1; j < target; j++ {
		if sentence1[s1end-j+1] != sentence2[s2end-j+1] {
			return false
		}
	}

	return (len1 > minLen && sentence1[len1-target] == ' ') ||
		(len2 > minLen && sentence2[len2-target] == ' ')
}

func main() {
	println(SentenceSimilarity3("Hello Jane", "Hello my name is Jane"), true)
	println(SentenceSimilarity3("Frog cool", "Frogs are cool"), false)
	println(SentenceSimilarity3("My name is Haley", "My Haley"), true)
	println(SentenceSimilarity3("of", "A lot of words"), false)
	println(SentenceSimilarity3("Eating right now", "Eating"), true)
	println(SentenceSimilarity3("Eatings right now", "Eating"), false)
	println(SentenceSimilarity3("Now", "Eating Now"), true)
	println(SentenceSimilarity3("Now", "Eating SNow"), false)
	println(SentenceSimilarity3("A A", "A aA"), false)
	println(SentenceSimilarity3("C", "CB B C"), true)
	println(SentenceSimilarity3("Hello good Jane", "Hello I good I Hello good Jane"), true)
}
