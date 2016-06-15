#! /usr/bin/python

import os
import sys

if len(sys.argv) != 4:
	print "usage: " + sys.argv[0] + " <source directory> <csv with emails, names> <output csv>"
	sys.exit( -1 )

src = sys.argv[1]
emailNames = sys.argv[2]
outputFile = sys.argv[3]

nameCombos = {}

# Read in User names of Enron Email Boxes
input = open(os.path.join(os.getcwd(), emailNames), 'r')

names = input.readlines()

input.close()

for i in names:
	j = str.split(i, ',')
	emailAddress = j[0]
	line = i.replace('\n','')
	nameCombos[emailAddress] = line

out = open(os.path.join(os.getcwd(), outputFile), 'w')

out.write("folder,mailbox,last,first,gender,count\n")

for i in nameCombos.keys():
	if os.path.exists(os.path.join(os.getcwd(), src, i)):
		cnt = len(os.listdir(os.path.join(os.getcwd(), src, i)))
		out.write(nameCombos[i] + "," + str(cnt) + "\n")

out.close()