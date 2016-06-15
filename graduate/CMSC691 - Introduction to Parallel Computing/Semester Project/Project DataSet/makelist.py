#! /usr/bin/python

import os
import sys

if len(sys.argv) != 2:
	print "usage: ", sys.argv[0], " <input file>"
	sys.exit(-1)

inputfile = os.path.join(os.getcwd(), sys.argv[1])

f = open(inputfile, 'r')

stuff = f.readlines()

f.close()

for i in stuff:
	j = i.replace('\n','')
	j = j.replace(' ','')
	print "{\"" + j + "\", 0},"