#!/usr/bin/perl -w

# Name:   Patrick Trinkle
# Course: CMSC433
# Date:   February

# Print all lines that contain an email address
# from any of the umbc.edu domains.
#
# i.e. "student@umbc.edu" qualifies
#      "john.smith@umbc.edu" qualifies
#      "nobody@cs.umbc.edu" qualifies
#      "nobody@umbc.com" does not

while (<>) {
  print if /.*@.*umbc\.edu\b/;
}

