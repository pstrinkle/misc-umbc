#!/usr/bin/perl -w

# Name: Patrick Trinkle
# Course: CMSC433
# Project: P2
# Email: tri1@umbc.edu
# File: edit.cgi

$ENV{PATH} = "/usr/bin";

use CGI;
use CGI::Carp qw(fatalsToBrowser);

# build web content
print "Content-type: text/html\n\n";

print <<HEADER;
<html>
  <head>
  <title>Edit Event</title>
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

print "<div class=\"form\">\n";
print "<h1>Edit Event</h1>\n";

if ( !$query->param('posted') ) { 

    $id = $query->param('id');
    $index = $query->param('index');

    $event = $hash_of_events{$id}[$index];

    @items = $event =~ m/(.+)\|\|(.+)/;

print <<EVENT;
<form action="edit.cgi" method="post">
    <table>
        <tr>
            <td class="label"><label for="name">Name<sup>&#8224;</sup>:</label></td>
            <td class="input"><input id="name" name="name" value="$items[0]" /></td>
        </tr>
        <tr>
            <td class="label"><label for="id">Date<sup>&#8224;</sup>:</label></td>
            <td class="input"><input id="date" name="date" value="$id" /></td>
        </tr>
        <tr>
            <td class="label" valign="top"><label for="details">Details:</label></td>
            <td class="input"><div><textarea id="details" name="details">$items[1]</textarea></div></td>
        </tr>
        <tr>
            <td colspan="2"><sup>&#8224;</sup> Denotes required field</td>
        </tr>
        <tr>
            <td class="buttons" colspan="2">
	        <input type="hidden" value="$index" name="index" />
		<input type="hidden" value="1" name="posted" />
                <input type="button" value="Cancel" onclick="javascript:window.close();"/>
                <input type="submit" value="Edit Event" style="font-weight: bold" />
            </td>
        </tr>
    </table>
</form>
EVENT

}
else
{
    $name = $query->param('name');
    $date = $query->param('date');
    $index = $query->param('index');
    $details = $query->param('details');

    $details =~ s/</&lt;/g;
    $details =~ s/>/&gt;/g;
    $name =~ s/</&lt;/g;
    $name =~ s/>/&gt;/g;

    if ($details eq "") {
        $details = " ";
    }

    # replace current
    $hash_of_events{$date}[$index] = $name . "||" . $details;

    # add it to file
    open(OUT, "> $file");

    foreach $eventkey ( keys %hash_of_events ) {

        $events = $hash_of_events{$eventkey};

        foreach $event ( @$events ) {

                @items = $event =~ m/(.+)\|\|(.+)/;
                print OUT "$eventkey $items[0] \"$items[1]\"\n";
        }
    }

    close(OUT);

    print "<p>Successfully editted event</p>\n";
    print "<p><a href=\"javascript:window.close();\">Close Window</a></p>";
}

print "</div>\n";

print <<FOOTER;
</body>
</html>
FOOTER
