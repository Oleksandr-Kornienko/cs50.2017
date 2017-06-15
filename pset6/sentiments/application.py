from flask import Flask, redirect, render_template, request, url_for

import helpers
import tweets
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweetss = helpers.get_user_timeline(screen_name)

    # TODO
    positive, negative, neutral = 0.0, 0.0, 0.0
    positives, negatives = [], []
    analyzer = Analyzer(positives, negatives)
    for tweet in tweetss:
        score = analyzer.analyze(tweet)
        if score > 0.0:
            positive += 1
        elif score < 0.0:
            negative += 1
        else:
            neutral += 1
    total = (positive + negative + neutral)

    

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
