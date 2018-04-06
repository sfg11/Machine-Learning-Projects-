'''
Description:
Sentiment analysis in python to analyzing tweets and determine its positive,
negative or neutral emotion.
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

searchTerm = input("enter keyword/hashtag or username to search about:")
numTweets = int(input("Enter how many tweets to analyze:"))

tweets = tweepy.Cursor(api.search, q=searchTerm).items(numTweets)

positive = 0
neutral = 0
negative = 0
polarity = 0
count = 20

for tweet in tweets:
    print(tweet.text)
    analysis = TextBlob(tweet.text)
    polarity += analysis.sentiment.polarity

    if(analysis.sentiment.polarity == 0):
        neutral += 1
    elif(analysis.sentiment.polarity < 0.00):
        negative += 1
    elif(analysis.sentiment.polarity > 0.00):
        positive += 1
# end for

positive = percentage(positive, numTweets)
negative = percentage(negative, numTweets)
neutral = percentage(neutral, numTweets)
polarity = percentage(polarity, numTweets)

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
plt.legend(patches, labels, loc ="best")
plt.title('How people are reacting on ' + searchTerm + ' by analyzing ' + str(numTweets) + ' Tweets ')
plt.axis('equal')
plt.tight_layout()
plt.show()
