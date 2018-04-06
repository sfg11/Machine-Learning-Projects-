from tweepy import API
from tweepy import Cursor
from tweepy import OAuthHandler
from tweepy import TweepError

from twitter_keys import APP_KEYS

from utils_misc import clean_text
from utils_misc import get_tweet_text




class TwitterMiner(object):

	""" Represents a Twitter data miner
	Attributes:
	----------
		API:
		    type: tweepy.API
		    info: object used to make connection with Twitter
	"""




	def __init__(self, token_key, token_secret):

		""" Creates a Twitter miner object
		Arguments:
		----------
			token_key:
				type: string
				info: identifies the user
			token_secret:
				type: string
				info: accompanies the token key
		"""

		try:
			consumer_key = APP_KEYS['consumer_key']
			consumer_secret = APP_KEYS['consumer_secret']

			auth = OAuthHandler(consumer_key, consumer_secret)
			auth.set_access_token(token_key, token_secret)

			self.API = API(auth)

		except TweepError:
			exit('Unable to create the tweepy API object')




	def get_user_tweets(self, user, word, depth = 1000):

		""" Generator that returns the 'depth' most recent user tweets
		Arguments:
		----------
			user:
				type: string
				info: Twitter user account without the '@'
			word:
				type: string (lowercase)
				info: word used to filter the tweets
			depth:
				type: int (optional)
				info: number of tweets to retrieve
		Yield:
		----------
			tweet_text:
				type: string
				info: cleaned tweet text
		"""

		try:
			cursor = Cursor(
				method = self.API.user_timeline,
				user_id = user,
				count = 200,
				tweet_mode = 'extended'
			)

			for tweet in cursor.items(depth):
				tweet_text = get_tweet_text(tweet)
				tweet_text = clean_text(tweet_text)

				if word in tweet_text: yield tweet_text

		except TweepError:
			exit('Unable to retrieve tweets from ' + user)




	def search_tweets(self, query, lang, depth = 1000):

		""" Generator that returns the 'depth' most recent user tweets
		Arguments:
		----------
			query:
				type: string
				info: string with logic operations (AND, OR...)
			lang:
				type: string
				info: language abbreviation to filter the tweets
			depth:
				type: int (optional)
				info: number of tweets to retrieve
		Yield:
		----------
			tweet_text:
				type: string
				info: cleaned tweet text
		"""

		try:
			cursor = Cursor(
				method = self.API.search,
				q = query,
				lang = lang,
				count = 100,
				tweet_mode = 'extended'
			)

			for tweet in cursor.items(depth):
				tweet_text = get_tweet_text(tweet)
				tweet_text = clean_text(tweet_text)

				yield tweet_text

		except TweepError:
			exit('Unable to find ' + str(depth) + ' tweets')
