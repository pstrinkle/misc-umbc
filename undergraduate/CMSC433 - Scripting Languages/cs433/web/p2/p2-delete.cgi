#!/usr/bin/perl -w

# Name: Patrick Trinkle
# Course: CMSC433
# Project: P2
# Email: tri1@umbc.edu
# File: delete.cgi

$ENV{PATH} = "/usr/bin";

use CGI;
use CGI::Carp qw(fatalsToBrowser);

# build web content
print "Content-type: text/html\n\n";

print <<HEADER;
<html>
  <head>
  <title>Delete Event</title>
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

print "      <div class=\"form\">\n";
print "      <h1>Delete Event</h1>\n";

if ( !$query->param('posted') ) {

    $id = $query->param('id');
    $index = $query->param('index');

    $qevent = $hash_of_events{$id}[$index];

    @items = $qevent =~ m/(.+)\|\|(.+)/;

print <<EVENT;
<form action="delete.cgi" method="post">
    <table>
        <tr>
           <td class="label">Title:</td>
           <td class="input">$items[0]</td>
       </tr>
       <tr>
            <td class="label">Date:</td>
            <td class="input">$id</td>
        </tr>
        <tr>
            <td class="label">Details:</td>
            <td class="input">$items[1]</td>
        </tr>
        <tr>
            <td class="buttons" colspan="2">
                <input type="hidden" value="$id" name="string" />
                <input type="hidden" value="$index" name="index"/>
		<input type="hidden" value="1" name="posted"/>
                <input type="button" value="Cancel" onclick="javascript:window.close();"/>
                <input type="submit" value="Delete Event" style="font-weight: bold" />
            </td>
        </tr>
    </table>
</form>
EVENT

}
else {

    $index = $query->param('index');
    $id = $query->param('string');
    
    $queryevent = $hash_of_events{$id}[$index];

    open(OUT, "> $file");

    foreach $eventkey ( keys %hash_of_events ) {

	$events = $hash_of_events{$eventkey};

	foreach $event ( @$events ) {

	    if ( $event ne $queryevent ) {
		@items = $event =~ m/(.+)\|\|(.+)/;
		print OUT "$eventkey $items[0] \"$items[1]\"\n";
	    }
	}
    }

    close(OUT);

    print "<p>Successfully deleted event</p>\n";
    print "<p><a href=\"javascript:window.close();\">Close Window</a></p>\n";
}

print "        </div>\n";

print <<FOOTER;
</body>
</html>
FOOTER
