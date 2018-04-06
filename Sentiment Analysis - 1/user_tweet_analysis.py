'''
Description:
Sentiment analysis in python to analyzing tweets and determine its positive,
negative or neutral emotion.
Use: search for a user (for example @RealDonaldTrump) and # of tweets
run: python user_tweet_analyis.py --user @RealDonaldTrump --count 200

Tools used:
 - Tweepy: a python library for accessing the Twitter API
 - http://tweepy.readthedocs.io/en/v3.5.0/

 - Textblob: a python library for processing textual data, it provides a API
             for natural language processing tasks such as sentiment analysis
 - http://textblob.readthedocs.io/en/dev/

'''
import argparse
import tweepy
from tweepy import OAuthHandler
from textblob import TextBlob

import matplotlib.pyplot as plt

def percentage(part, whole):
    return 100 * float(part)/float(whole)

# twitter api
consumer_key = 'DmHQaI0c3zyiHi8VaHw6fXex7'
consumer_secret = 'IJL6XiU3HicJjSGUa7ZlqMgQBQpeYU9qHZPcqLqfwbD60lFCj6'
access_token= '939982357339234305-FWK4D0r5ZH2fdsNEJCgKnJ2DErMBhZq'
access_secret= '8CUGQ2jxmkdshI0c3XxFTVltnTzPHam5mbN5juUcNSz1Y'

#authentification
auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_secret)

#get api
api = tweepy.API(auth)


# Command Line
parser = argparse.ArgumentParser(prog="tweet-analysis", description="Analysis of tweets")
parser.add_argument("--user", type=str, help="Twitter's username", required=False)

parser.add_argument("--count", type=int, help="Number of tweets", required=False)
args=parser.parse_args()
tweets = tweepy.Cursor(api.user_timeline, screen_name=args.user).items(args.count)


positive = 0
neutral = 0
negative = 0
polarity = 0
count = 0


#Get status_texts
for tweet in tweets:
#for tweet in tweets:
    print(tweet.text)
    analysis = TextBlob(tweet.text)
    polarity += analysis.sentiment.polarity

    if(analysis.sentiment.polarity == 0.00):
        neutral += 1
    elif(analysis.sentiment.polarity < 0.00):
        negative += 1
    elif(analysis.sentiment.polarity > 0.00):
        positive += 1
# end for
positive = percentage(positive, args.count)
negative = percentage(negative, args.count)
neutral = percentage(neutral, args.count)
polarity = percentage(polarity, args.count)

positive = format(positive, '.2f')
neutral = format(neutral, '.2f')
negative = format(negative, '.2f')


if (polarity == 0):
    print("Neutral")
elif (polarity < 0.00):
    print("Negative")
elif (polarity > 0.00):
    print("Positive")

labels = ['Positive ['+str(positive)+'%]', 'Neutral ['+str(neutral)+'%]', 'Negative ['+str(negative)+'%]']
sizes = [positive, neutral, negative]
colors = ['green', 'gold', 'red']
patches, texts = plt.pie(sizes, colors = colors, startangle = 90)
plt.legend(patches, labels, loc="best")
plt.title('Based off of the last ' + str(args.count) + ' tweets by @' +args.user + ' ' )
plt.axis('equal')
plt.tight_layout()
plt.show()
