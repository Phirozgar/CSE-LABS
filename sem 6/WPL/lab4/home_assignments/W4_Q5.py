class WordReverser:
    def reverse_words(self, s):
        words = s.split()
        return " ".join(reversed(words))

reverser = WordReverser()
print(reverser.reverse_words("PHIROZ"))
