package main

func SentenceSimilarity3(sentence1, sentence2 string) bool {
	lsp := -1
	i := 0

	minLen := min(len(sentence1), len(sentence2))

	for i = 0; i < minLen; i++ {
		if sentence1[i] != sentence2[i] {
			break
		}
		if sentence1[i] == ' ' {
			lsp = i
		}
	}

	if i == minLen &&
		((len(sentence1) == len(sentence2)) ||
			(len(sentence1) > minLen && sentence1[i] == ' ') ||
			(len(sentence2) > minLen && sentence2[i] == ' ')) {
		return true
	}

	target := minLen - lsp
	for i = 1; i < target; i++ {
		if sentence1[len(sentence1)-i] != sentence2[len(sentence2)-i] {
			return false
		}
	}

	return ((len(sentence1) > minLen) && (sentence1[len(sentence1)-target] == ' ')) ||
		((len(sentence2) > minLen) && (sentence2[len(sentence2)-target] == ' '))
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
