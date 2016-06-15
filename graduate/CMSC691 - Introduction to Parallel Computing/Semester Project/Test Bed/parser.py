#!/usr/bin/env python

# --------------------------------------------------------------------------------
# Patrick Trinkle
# CMSC691
# Spring 2009
# Note: This script was written strictly to gather meta-data
#       against the Enron Corpus
#
# Desc: Walk through directory hierarchy by user folder. For each
#       message, calculate the term frequencies and then write
#       the lower-case message body to a new file in a folder 
#       indicating the author (this sorts the emails by author)
#       Any email not sent from an Enron employee is deleted from
#       the OS (future versions may just ignore file, versus deleting.
#
# --------------------------------------------------------------------------------

# Import Libraries
import email
import os
import re
import hashlib

emails = set()
emailAddresses = set()
log = ""

# --------------------------------------------------------------------------------
# place_by_author
# Input: Complete X-From Field, Email Payload
def place_by_author(field_from, payload):
	"""This function writes the payload in the user dir"""

	field_from = field_from.replace('<', '')
	field_from = field_from.replace('>', '')
	field_from = field_from.replace(' ', '')
	field_from = field_from.replace('"', '')

	outdir = os.path.join(os.getcwd(), "sorted", field_from)

	dig = hashlib.sha256(payload).hexdigest()

	if not os.path.exists(outdir):
		os.mkdir(outdir)

	if os.path.isfile(os.path.join(outdir, dig + ".txt")):
		print "SAME SHA256 AND SAME AUTHOR, POSSIBLE COLLISION!"
	else:
		out = open(os.path.join(outdir, dig + ".txt"), 'w')
		out.write(payload)
		out.close()

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
	global emails
	global log

	tokenset = {}
	digest = ""

	fp = open(path, 'r')
	emailMsg = email.message_from_file(fp)
	fp.close()

	if re.search("\@enron\.com", emailMsg['From']):

		field_from = emailMsg['From'].replace('<', '')
		field_from = field_from.replace('>', '')
		field_from = field_from.replace(' ', '')
		field_from = field_from.replace('"', '')

		emailAddresses.add(field_from + ":" + str(emailMsg['X-From']))

		digest = hashlib.sha512(field_from + "\n" + emailMsg.get_payload().lower()).hexdigest()

		if digest in emails:
		#if field_from + "\n" + emailMsg.get_payload().lower() in emails:
			log.write("Found Duplicate Email: " + path + "\n")
			#os.remove(path)
		else:
			emails.add(digest)
			#emails.add(field_from + "\n" + emailMsg.get_payload().lower())
			tokenset = parse_body(emailMsg.get_payload().lower())
			place_by_author(emailMsg['From'], emailMsg.get_payload().lower())
	else:
		# Non-Enron Email
		log.write("From: " + emailMsg['From'] + " Deleting: " + path + "\n")
		#os.remove(path)

	#print "File (", path, ") Tokens: ", tokenset
	return tokenset

# --------------------------------------------------------------------------------
# process_dir
# Input: full path to dir of files
def process_dir(path):
	"""This function processes the files in a folder"""
	directorytokens = {}
	files = os.listdir(path)

	for file in files:
		if os.path.isfile(os.path.join(path, file)):
			filetokens = process_file(os.path.join(path, file))
			for t in filetokens.keys():
				if t in directorytokens:
					directorytokens[t] += filetokens[t]
				else:
					directorytokens[t] = filetokens[t]
	#print "Directory (", path, ") Tokens: ", directorytokens
	return directorytokens

# --------------------------------------------------------------------------------
# process_user
# Input: full path to user dir
def process_user(user_path):
	"""This function processes the folders for a user!"""
	usertokens = {}
	dirs = os.listdir(user_path)

	for dir in dirs:
		if os.path.isdir(os.path.join(user_path, dir)):
			dirtokens = process_dir(os.path.join(user_path, dir))
			for t in dirtokens.keys():
				if t in usertokens:
					usertokens[t] += dirtokens[t]
				else:
					usertokens[t] = dirtokens[t]
		else:
			print "Is a File! (so skipping-known bug): ", os.path.join(user_path, dir)
	#print "User (", user_path, ") Tokens: ", usertokens
	return usertokens

# --------------------------------------------------------------------------------
# --- Main Function ---
# --------------------------------------------------------------------------------

# Walk through directory of files
root_dir = os.path.join(os.getcwd(), "Pure DataSet")
users = os.listdir(root_dir)
totaltokens = {}

# Set up Sorted Output Path
sorteddirs = os.path.join(os.getcwd(), "Sorted DataSet")

if os.path.exists(sorteddirs):
	print "Sorted Directory Already Exists"
else:
	print "Sorted Directory Does Not Yet Exist"
	os.mkdir(sorteddirs)
	print "Created"

log = open(os.path.join(os.getcwd(), "log.txt"), 'w')

for user in users:
	if os.path.isdir(os.path.join(root_dir, user)):
		user_tokens = process_user(os.path.join(root_dir, user))
		for t in user_tokens.keys():
			if t in totaltokens:
				totaltokens[t] += user_tokens[t]
			else:
				totaltokens[t] = user_tokens[t]
	else:
		print "Strange File found instead of user directory!"
	print "Finished User", user

log.close()

# Sort Results by Decreasing Value
sorted_tokens = [(v, k) for k, v in totaltokens.items()]
sorted_tokens.sort()
sorted_tokens.reverse()
sorted_tokens = [(k, v) for v, k in sorted_tokens]

# List Top 50 with Value
if len(sorted_tokens) < 50:
	for k, v in sorted_tokens:
		print k, v
else:
	for i in range(50):
		print sorted_tokens[i]

# This is for Processing Email Addresses
emailOut = open(os.path.join(os.getcwd(), "emails.txt"), 'w')

sorted_addresses = []

for i in emailAddresses:
	sorted_addresses.append(i)

sorted_addresses.sort()

for i in emailAddresses:
	emailOut.write(i + "\n")

emailOut.close()
