#! /usr/bin/env python

import os
import sys
import re

if len(sys.argv) != 2:
	print "usage: " + sys.argv[0] + " <input dir>"
	sys.exit( -1 )

srcdir = sys.argv[1]

to_email = set()
from_email = set()

# Walk through directory of files
root_dir = os.path.join(os.getcwd(), srcdir)

def process_user(user_dir):
	global to_email
	global from_email
	global root_dir

	emails = os.listdir(os.path.join(root_dir, user_dir))

	for email in emails:
		contents = open(os.path.join(root_dir, user_dir, email), 'r').readlines()

		for content in contents:
			m = re.search("to:", content)
			if m:
				if content not in to_email:
					to_email.add(content)
			m = re.search("from: ", content)
			if m:
				if content not in from_email:
					from_email.add(content)

# ---Main---
users = os.listdir(root_dir)
cnt = len(users)

log = open(os.path.join(os.getcwd(), srcdir + "email_names_stuff.txt"), 'w')

us = 0
for user in users:
	us += 1

	# MiddleInitial..LastName
	m = re.search("\w\.\.\w+@enron", user)
	n = re.search("\w+\.\w+@enron", user)
	o = re.search("\w+@enron", user)

	if m:
		print "MI..Last: " + user
	elif n:
		print "First.Last: " + user
	elif o:
		print "Other: " + user
	else:
		print "Unmatched: " + user

	process_user(user)

	log.write("User: " + user + "\n")

# - To Lines
for i in to_email:
	print i

# - From Lines
for i in from_email:
	print i

log.close()
