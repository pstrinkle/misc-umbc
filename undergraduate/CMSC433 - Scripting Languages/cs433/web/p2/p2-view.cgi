#!/usr/bin/perl -w

# Name: Patrick Trinkle
# Course: CMSC433
# Project: P2
# Email: tri1@umbc.edu
# File: view.cgi

$ENV{PATH} = "/usr/bin";

use CGI;
use CGI::Carp qw(fatalsToBrowser);

# build web content
print "Content-type: text/html\n\n";

print <<HEADER;
<html>
  <head>
  <title>Event Details</title>
  <link rel="stylesheet" type="text/css" href="style.css" />
</head>
<body>
HEADER

# the events file
$file = "/afs/umbc.edu/users/t/r/tri1/pub/cs433/read-write/events.dat";

open(EVENTS, $file);

# you hash in with the string date: M-D-YYYY, and then it's an array of arrays
my %hash_of_events;

while ( <EVENTS> ) {
    if ( m/(\d+-\d+-\d+)\s+(.*)?"(.+)"/ ) {
        $date = $1;
        $event = $2;
	$details = $3;

        @current = $hash_of_events{$date};
        $lastindex = $#current;

        if ( $lastindex == 0 && $current[$lastindex] == '' ) {
            $hash_of_events{$date}[$lastindex] = $event . "||" . $details;
        }
        else {
            $lastindex++;
            $hash_of_events{$date}[$lastindex] = $event . "||" . $details;
        }
    }
}

close(EVENTS);

# check to see if there's a url thing
$query = new CGI;

$id = $query->param('id');
$index = $query->param('index');

$event = $hash_of_events{$id}[$index];

@items = $event =~ m/(.+)\|\|(.+)/;

print <<EVENTTOP;
      <div class="form">
        <h1>Event Details</h1>
<form action="#" method="post">
    <table>
        <tr>
EVENTTOP

print "           <td class=\"label\">Title:</td>\n";
print "           <td class=\"input\">$items[0]</td>\n";
print "       </tr>\n";
print "       <tr>\n";
print "            <td class=\"label\">Date:</td>\n";
print "            <td class=\"input\">$id</td>\n";
print "        </tr>\n";
print "        <tr>\n";
print "            <td class=\"label\">Details:</td>\n";
print "            <td class=\"input\">$items[1]</td>\n";

print <<EVENTBOTTOM;
        </tr>
        <tr>
            <td class="buttons" colspan="2">
                <input type="button" value="Ok" onclick="javascript:window.close();"/>
            </td>
        </tr>
    </table>
</form>
        </div>
EVENTBOTTOM

print <<FOOTER;
</body>
</html>
FOOTER
