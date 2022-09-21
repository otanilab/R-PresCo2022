import MeCab
import requests
import csv
import request


class Words:
    def __init__(self, sentence):
        tagger = MeCab.Tagger("-Owakati")
        self.words = tagger.parse(sentence).split()

class Morpheme:
    def __init__(self, words):
        self.bases = []
        tagger = MeCab.Tagger()
        for word in words:
            results = tagger.parse(word).split()
            result = results[1]
            result = result.split(',')
            self.bases.append((((result[6].split(':'))[-1]).split('/'))[0])

def translate(txt):
    key = request.key
    params = {
        "auth_key": key,
        "text": txt,
        "source_lang": 'JA',
        "target_lang": 'EN'
    }

    request = requests.post("https://api.deepl.com/v2/translate", data=params)
    result = request.json()
    return result["translations"][0]["text"]

with open('R-PresCo.csv') as f:
    reader = csv.reader(f)
    rows = [row for row in reader]
    for i in range(len(rows)):
        if rows[i-1][2] != "ある":
            del rows[i-1]
        words = Words(str(rows[i-1][3]))
        print(words.words)
        rows[i-1][3] = (Morpheme(words.words).bases)
        print(rows)

sentence = "入学式で集合写真を撮る"
words = Words(sentence)
print(words.words)

morphemes = Morpheme(words.words)
