#! /usr/bin/python

# Patrick Trinkle
# Spring 2009
# Finds duplicate documents in a corpus
# Probably not the fastest way of doing
# this because it does read in every 
# document

import os
import hashlib

hashes = {}
root = os.getcwd()
filepath = os.path.join(root, "Input", "files")

docs = os.listdir(filepath)

# calculate hash
for i in docs:
	contents = open(os.path.join(filepath, i)).read()
	dig = hashlib.sha512(contents).hexdigest()

	if dig in hashes.keys():
		print i + " is the same as " + hashes[dig]
	else:
		hashes[dig] = i
