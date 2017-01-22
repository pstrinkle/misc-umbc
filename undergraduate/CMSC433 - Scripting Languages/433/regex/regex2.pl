#!/usr/bin/perl -w

# Name:   Patrick Trinkle
# Course: CMSC433
# Date:   February

# Print all lines that open and then close the same XML tag.
# An opening XML tag looks like: "<foobar>"
# A closing XML tag looks like: "</foobar>"
#
# i.e. "<table>" does not qualify
#      "<p>Foo Bar Baz</p>" qualifies
#      "<p><b>Blah</b> - foo" qualifies


while (<>) {
  print if /<(\w+|\.|-|:)>.*<\/\1>/;
}

