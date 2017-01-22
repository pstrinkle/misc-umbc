#!/usr/bin/perl -w

# Name:   Patrick Trinkle
# Course: CMSC433
# Date:   February

# Print all lines that contain a valid time in any of the following formats:
#
# "HH:MM am" such as "12:34 am"
# "H:MM am" such as "8:01 am"
# "HH:MMam" such as "12:00am"
# "H:MMam" such as "9:18am"
# "HH:MM pm" such as "12:34 pm"
# "H:MM pm" such as "8:01 pm"
# "HH:MMpm" such as "12:00pm"
# "H:MMpm" such as "9:18pm"


while (<>) {
  print if /((\s|0)[1-9])|(1[0-2]):[0-5][0-9]\s*(am|pm)/i;
}

