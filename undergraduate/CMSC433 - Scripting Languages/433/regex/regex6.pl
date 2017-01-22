#!/usr/bin/perl -w

# Name:   Patrick Trinkle
# Course: CMSC433
# Date:   February

# Assume that you have a CSV (Comma Separated Value) file
# that contains the following values in each column:
#
# Last Name, First Name, Middle Initial, Phone, Email, Major
#
# Change the output to be in the following format:
#
# First Name Last Name (Email)
#
# i.e. "Hood, Daniel, J, 123-456-7890, danielhood@umbc.edu, CMSC"
#      becomes "Daniel Hood (danielhood@umbc.edu)"

while (<>) {
   s/(.*), (.*), \w, .*, (.*@.*), .*/$2 $1 ($3)/;
   print;
}

