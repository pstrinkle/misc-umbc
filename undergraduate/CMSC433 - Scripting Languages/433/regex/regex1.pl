#!/usr/bin/perl -w

# Name:   Patrick Trinkle
# Course: CMSC433
# Date:   February


# Print all lines that contain at least 3 vowels on them,
# vowels need not necessarily be consecutive or the same.
#
# i.e. "foo bar" qualifies
#      "fish and chips" qualifies
#      "UMBC UMCP" does not


while (<>) {
  print if /[aeiou].*[aeiou].*[aeiou]/i;
}

