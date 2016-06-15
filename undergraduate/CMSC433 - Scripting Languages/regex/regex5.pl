#!/usr/bin/perl -w

# Name:   Patrick Trinkle
# Course: CMSC433
# Date:   February

# if there exists are a pair of back-to-back duplicate words on a line,
# remove the extra duplicate word and the whitespace between them.
#
#
# i.e. "foo foo baz foo" -> "foo baz foo"
#      "foo bar foo" -> no change
#      "now is   is the time" -> "now is the time"
#      "foo foobar foobarbaz" -> no change 
#      "Foo.  Foo Bar" -> no change 

while (<>) {
   s/\b(\w+)\s{1,}\1/\1/;
   print;
}

