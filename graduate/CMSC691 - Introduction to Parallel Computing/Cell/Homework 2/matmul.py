#! /usr/bin/python

a = [[16,15,14,13],[13,12,11,10],[10,9,8,7],[7,6,5,4]]
b = [[16,15,14,13],[13,12,11,10],[10,9,8,7],[7,6,5,4]]
c = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]

def mulprint(i, j, k):
	print "c[", i, "][", j, "] += ",
	print "a[", i, "][", k, "] * ",
	print "b[", k, "][", j, "]"

print "A:"
for i in range(0, 4):
	print a[i]

print "B:"
for i in range(0, 4):
	print b[i]

print "C:"
for i in range(0, 4):
	print c[i]

for i in range(0, 4):
	for j in range(0, 4):
		for k in range(0, 4):
			print i, j, k
			mulprint(i, j, k)
			c[i][j] += a[i][k] * b[k][j]

print "C as Result:"
for i in range(0, 4):
	print c[i]

