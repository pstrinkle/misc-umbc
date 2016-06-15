#!/usr/bin/env python

# This calculates how many email files are in a folder
# Also, calculates the total number of emails; when
# used on a distinct sorted set this determines the
# number of unique emails (unique:=from_emailaddr + message)

import os
import sys

# --------------------------------------------------------------------------------
# --- Main Function ---
# --------------------------------------------------------------------------------

if len(sys.argv) != 2:
	print "usage: " + sys.argv[0] + " <input dir>"
	sys.exit( -1 )

root_dir = os.path.join(os.getcwd(), sys.argv[1])
users = os.listdir(root_dir)

emailCnts = {}

for u in users:
	emails = os.listdir(os.path.join(root_dir, u))
	emailCnts[u] = len(emails)

# Sort Results by Decreasing Value
sorted_tokens = [(v, k) for k, v in emailCnts.items()]
sorted_tokens.sort()
sorted_tokens.reverse()
sorted_tokens = [(k, v) for v, k in sorted_tokens]

for k, v in sorted_tokens:
	print k, v

total = 0

for i in emailCnts.keys():
	total += emailCnts[i]

print total