#!/usr/bin/env python

# Patrick Trinkle
# Spring 2009
# This removes any folder not in a newline seperated list

import os
import sys

# --------------------------------------------------------------------------------
# --- Main Function ---
# --------------------------------------------------------------------------------

if len(sys.argv) != 3:
	print "usage: " + sys.argv[0] + " <source dir> <list>"
	sys.exit( -1 )

source_dir = sys.argv[1]
list_file = sys.argv[2]

root_dir = os.path.join(os.getcwd(), source_dir)
users = os.listdir(root_dir)

emailAccts = open(os.path.join(os.getcwd(), list_file), 'r').readlines()
emailCnts = {}

cnt = len(users)
us = 0

# Process Folders
for u in users:
	us += 1
	if u + "\n" not in emailAccts:
		emails = os.listdir(os.path.join(root_dir, u))

		for i in emails:
			os.remove(os.path.join(root_dir, u, i))
		os.removedirs(os.path.join(root_dir, u))
	else:
		emailCnts[u] = len(os.listdir(os.path.join(root_dir, u)))

	print "done: (" + str((float(us)/cnt)*100) + "%)"

sorted_emailaddrs = [(k, v) for k, v in emailCnts.items()]
sorted_emailaddrs.sort()

for k, v in sorted_emailaddrs:
	print k + "," + str(v)

if len(emailCnts) != len(emailAccts):
	print "Lengths don't match"
else:
	print "Found all users"