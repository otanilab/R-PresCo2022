import MeCab


class Words:
    def __init__(self, sentence):
        tagger = MeCab.Tagger("-Owakati")
        self.words = tagger.parse(sentence).split()

class Morpheme:
    def __init__(self, words):
        self.morphemes = []
        tagger = MeCab.Tagger()
        for word in words:
            results = tagger.parse(word).split()
            surface, result = results[0], results[1]
            result = result.split(',')
            dict = {
                'surface':surface,
                'pos':result[0],
                'base':(((result[6].split(':'))[-1]).split('/'))[0]
            }
            self.morphemes.append(dict)

sentence = "入学式で集合写真を撮る"
words = Words(sentence)
print(words.words)

morphemes = Morpheme(words.words)
print(morphemes.morphemes)
