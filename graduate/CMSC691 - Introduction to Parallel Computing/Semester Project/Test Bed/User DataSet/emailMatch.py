#! /usr/bin/python

import os
import sys

if len(sys.argv) != 4:
	print "usage: " + sys.argv[0] + " <email garbage> <csv with names> <output csv>"
	sys.exit( -1 )

emailGarbage = sys.argv[1]
emailNames = sys.argv[2]
outputFile = sys.argv[3]

emailAddress = set()
nameCombos = {}

# Read in the actual processed email names and addresses
input = open(os.path.join(os.getcwd(), emailGarbage), 'r')

garbage = input.readlines()

input.close()

# Read in User names of Enron Email Boxes
input = open(os.path.join(os.getcwd(), emailNames), 'r')

names = input.readlines()

input.close()

# Strip out and get email addresses
for i in garbage:
	j = str.split(i, ':')
	emailAddress.add(j[0])

for i in names:
	j = str.split(i, ',')
	last = str.lower(j[1])
	first = str.lower(j[2])
	nameCombos[first + "." + last + "@enron.com"] = i

out = open(os.path.join(os.getcwd(), outputFile), 'w')

out.write("folder,mailbox,last,first,gender\n")

for i in nameCombos.keys():
	if i in emailAddress:
		out.write(i + "," + nameCombos[i])

out.close()