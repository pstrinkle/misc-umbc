#!/usr/bin/env python

# Patrick Trinkle
# Spring 2009
# This removes any folder with fewer items than the threshold

import os
import sys

# --------------------------------------------------------------------------------
# --- Main Function ---
# --------------------------------------------------------------------------------

if len(sys.argv) != 4:
	print "usage: " + sys.argv[0] + " <source dir> <minimum threshold> <output filename>"
	sys.exit( -1 )

source_dir = sys.argv[1]
minimum_threshold = int(sys.argv[2])
outputfilename = sys.argv[3]

print "Source Directory: " + source_dir
print "Minimum Threshold: " + str(minimum_threshold)
print "Output Filename: " + outputfilename

root_dir = os.path.join(os.getcwd(), source_dir)
users = os.listdir(root_dir)

emailCnts = {}

log = open(os.path.join(os.getcwd(), outputfilename), 'w')

cnt = len(users)
us = 0

# Process Folders
for u in users:
	us += 1

	emails = os.listdir(os.path.join(root_dir, u))
	count = len(emails)

	# Are there fewer than threshold emails in the folder
	# If there are fewer, delete them and the folder
	if count < minimum_threshold:
		log.write(str(count) + " emails in " + u + "\n")

		for i in emails:
			os.remove(os.path.join(root_dir, u, i))
		os.removedirs(os.path.join(root_dir, u))

		print "Directory: " + u + " has too few (" + str(count) + ") removed. (" + str((float(us)/cnt)*100) + "%)"
	else:
		emailCnts[u] = count

log.close()

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
