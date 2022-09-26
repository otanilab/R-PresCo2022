import MeCab
import requests
import csv
import key
import re

class Words:
    def __init__(self, sentence):
        tagger = MeCab.Tagger("-Owakati")
        self.words = tagger.parse(sentence).split()

class Morpheme:
    def __init__(self, words):
        self.morphemes = []
        tagger = MeCab.Tagger()
        for word in words:
            results = tagger.parse(word).split(',')
            self.morphemes.append(results)

def extract(morphemes):
    result = []
    for morpheme in morphemes:
        word, word_class = morpheme[0].split('\t')
        if word_class == '名詞' or word_class == '形容詞':
            result.append(word)
    return result

def translate(texts, key):
    print(texts)
    en_words = []
    key = key
    for txt in texts:
        params = {
            "auth_key": key,
            "text": txt,
            "source_lang": 'JA',
            "target_lang": 'EN'
        }
        request = requests.post("https://api.deepl.com/v2/translate", data=params)
        result = request.json()
        result["translations"][0]["text"] = re.sub("\(.+?\)", "", result["translations"][0]["text"])
        en_words.append(result["translations"][0]["text"])
    return en_words

with open('/Users/so/Desktop/R-PresCo2022/genImg/R-PresCo.csv') as f:
    reader = csv.reader(f)
    words = []
    rows = [row for row in reader]
    del rows[0]
    for row in rows:
        if row[2] == 'ある':
            words = Words(row[3])
            morphemes = Morpheme(words.words)
            jap_words = extract(morphemes.morphemes)
            en_words = translate(jap_words ,key.key)
            print(en_words)
