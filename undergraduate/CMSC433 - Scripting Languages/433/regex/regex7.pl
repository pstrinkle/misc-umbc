#!/usr/bin/perl -w

# Name:   Patrick Trinkle
# Course: CMSC433
# Date:   February

# Remove any C-style comments (/* ... */) from each line
#
# i.e. "int foo; /* foo bar */" -> "int foo; "
#      "int bar; /* comment continued on next line" -> unchanged
#      "if( 1 /* always true */)" -> "if( 1 )"

while (<>) {
   s@(/\*.*\*/)@@;
   print;
}

