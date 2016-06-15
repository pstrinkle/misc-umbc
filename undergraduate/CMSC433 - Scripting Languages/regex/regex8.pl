#!/usr/bin/perl -w

# Name:   Patrick Trinkle
# Course: CMSC433
# Date:   February

# Reduce all duplicate adjacent characters to a single character
#
# i.e. "bbb" -> "b"
#      "1111441" -> "141"
#      space-space-space -> space

while (<>) {
   s/(.)\1{1,}/$1/g;
   print;
}

