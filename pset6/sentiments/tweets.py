#!/usr/bin/env python3

import os
import sys
import html
import helpers

from twython import Twython
from twython import TwythonAuthError, TwythonError, TwythonRateLimitError
from analyzer import Analyzer
from termcolor import colored

def main():

    # ensure proper usage
    if len(sys.argv) != 2:
        sys.exit("Usage: ./tweets word")
    
    tweets = helpers.get_user_timeline(sys.argv[1].lstrip("@")) 

    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)
    # analyze word
    for i in tweets:
        score = analyzer.analyze(i)
        if score > 0.0:
            print(colored(str(score)+ " " + i, "green"))
        elif score < 0.0:
            print(colored(str(score)+ " " + i, "red"))
        else:
            print(colored(str(score)+ " " + i, "yellow"))
    
    
if __name__ == "__main__":
    main()