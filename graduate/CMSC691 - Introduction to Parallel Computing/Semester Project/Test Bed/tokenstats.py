#!/usr/bin/env python

# Calculate some Token Statistics for a sorted set
# of the Enron Corpus

# This can only process data that is sorted

import email
import os
import re
import sys

if len(sys.argv) != 2:
	print "usage: " + sys.argv[0] + " <input dir>"
	sys.exit( -1 )

srcdir = sys.argv[1]

# --------------------------------------------------------------------------------
# parse_body
# Input: message body
def parse_body(message):
	"""This function processes the message body!"""	
	tokens = {}

	without = re.split("\W+", message)

	for t in without:
		if t != '':
			if t in tokens:
				tokens[t] += 1
			else:
				tokens[t] = 1
	return tokens

# --------------------------------------------------------------------------------
# process_file
# Input: full path
def process_file(path):
	"""This function processes the email file!"""
	tokenset = {}

	fp = open(path, 'r')
	emailMsg = email.message_from_file(fp)
	fp.close()

	tokenset = parse_body(emailMsg.get_payload().lower())

	return tokenset

# --------------------------------------------------------------------------------
# process_user
# Input: full path to user dir
def process_user(user_path):
	"""This function processes the folders for a user!"""
	usertokens = {}
	emailtokens = {}

	emails = os.listdir(user_path)

	for email in emails:
		emailtokens = process_file(os.path.join(user_path, email))
		for t in emailtokens.keys():
			if t in usertokens:
				usertokens[t] += emailtokens[t]
			else:
				usertokens[t] = emailtokens[t]

	return usertokens

# --------------------------------------------------------------------------------
# --- Main Function ---
# --------------------------------------------------------------------------------

# Walk through directory of files
root_dir = os.path.join(os.getcwd(), srcdir)
users = os.listdir(root_dir)

userTokenStats = {}
totaltokens = {}

log = open(os.path.join(os.getcwd(), srcdir + "_statlog.txt"), 'w')

cnt = len(users)
us = 0

for user in users:
	us += 1
	user_tokens = process_user(os.path.join(root_dir, user))
	userTokenStats[user] = len(user_tokens)

	log.write("User: " + user + " " + str(userTokenStats[user]) + " tokens found\n")

	for t in user_tokens.keys():
		if t in totaltokens:
			totaltokens[t] += user_tokens[t]
		else:
			totaltokens[t] = user_tokens[t]
	print "Finished User", user + " (" + str((float(us)/cnt)*100) + "%)"

maxKeys = 0
minKeys = 10000000
avgKeys = 0

for num in userTokenStats.values():
	if num > maxKeys:
		maxKeys = num
	if num < minKeys:
		minKeys = num
	avgKeys += num

log.write("Maximum Keys: " + str(maxKeys) + "\n")
log.write("Minimum Keys: " + str(minKeys) + "\n")
log.write("Average Keys: " + str(avgKeys / len(userTokenStats)) + "\n")
log.write("Total Number of Terms: " + str(len(totaltokens)) + "\n")
log.close()

# Sort Results by Decreasing Value
sorted_tokens = [(v, k) for k, v in totaltokens.items()]
sorted_tokens.sort()
sorted_tokens.reverse()
sorted_tokens = [(k, v) for v, k in sorted_tokens]

# List Top 75 with Value
if len(sorted_tokens) < 75:
	for k, v in sorted_tokens:
		print k, v
else:
	for i in range(75):
		print sorted_tokens[i]
