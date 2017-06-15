import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positives = []
        self.negatives = []
        fnegative = open("negative-words.txt")
        for line in fnegative:
                if line.startswith((";", " ")):
                    continue
                else:
                    self.negatives.extend(line.split())
        fpositive = open("positive-words.txt")
        for line in fpositive:
                if line.startswith((";", " ")):
                    continue
                else:
                    self.positives.extend(line.split())


        
    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        score = 0
        for token in tokens:
            token.lower()
            words = token.split()
            for word in words:
                if word in self.positives:
                    score = score + 1
                elif word in self.negatives:
                    score = score - 1
                else :
                    score = score + 0
        return score
