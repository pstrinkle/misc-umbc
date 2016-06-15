#!/usr/bin/perl -w

# Name: Patrick Trinkle
# Course: CMSC433
# Project: P2
# Email: tri1@umbc.edu
# File: index.cgi
# Files: index.cgi view.cgi edit.cgi delete.cgi add.cgi
# Data File: /afs/umbc.edu/users/t/r/tri1/pub/cs433/read-write/events.dat
# Data File Format: M-D-YYYY Event "Details"

$ENV{PATH} = "/usr/bin";

use CGI;
use CGI::Carp qw(fatalsToBrowser);

# the events file
$file = "/afs/umbc.edu/users/t/r/tri1/pub/cs433/read-write/events.dat";

open(EVENTS, $file);

# you hash in with the string date: M-D-YYYY, and then it's an array
my %hash_of_events;

while ( <EVENTS> ) {
    if ( m/(\d+-\d+-\d+)\s+(.*)?".+"/ ) {
	$date = $1;
	$event = $2;

	@current = $hash_of_events{$date};
	$lastindex = $#current;

	if ( $lastindex == 0 && $current[$lastindex] == '' ) {
	    $hash_of_events{$date}[$lastindex] = $event;
	}
	else {
	    $lastindex++;
	    $hash_of_events{$date}[$lastindex] = $event;
	}
    }
}

close(EVENTS);

# the structures holding the months
@months = ("January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December");
%backmonths = ("January" => '0',
	       "February" => '1',
	       "March" => '2',
	       "April" => '3',
	       "May" => '4',
	       "June" => '5',
	       "July" => '6',
	       "August" => '7',
	       "September" => '8',
	       "October" => '9',
	       "November" => '10',
	       "December" => '11');

# check to see if there's a url thing
$query = new CGI;

$month = $query->param('month');
$year = $query->param('year');
$cleanMonth = '';
$cleanYear = '';

if($month =~ m/(\d+)/) {
    $cleanMonth = $1;
} else {
    $cleanMonth = (localtime(time))[4] + 1;
}

if($year =~ m/(^\d{4})$/) {
    $cleanYear = $1;
} else {
    $cleanYear = (localtime(time))[5] + 1900;
}

if($cleanMonth < 1 || $cleanMonth > 12) {
    $cleanMonth = '';
}
if($cleanYear < 0) {
    $cleanYear = '';
}

@cal = `cal $cleanMonth $cleanYear`;
$titlebar = $cal[0];

if ( $titlebar =~ m/(\w+)\s(\d+)/ ) { 
    $theMonth = $1;
    $theYear = $2;
}

$cleanYear = $theYear;
$cleanMonth = $backmonths{$theMonth} + 1;
# make it no longer point to the array value

$preMonth = $cleanMonth - 1;
$nextMonth = $cleanMonth + 1;
$preYear = $cleanYear;
$nextYear = $cleanYear;

if ( $preMonth < 1 ) {
    $preMonth = 12;
    $preYear = $cleanYear - 1;
}

if ( $nextMonth > 12 ) {
    $nextMonth = 1;
    $nextYear = $cleanYear + 1;
}

# build web content
print "Content-type: text/html\n\n";

print <<HEADER;
<html>
  <head>
  <title>Calendar</title>
  <style type="text/css" media="screen, print">
    body { text-align: center; font-family: sans-serif; margin: 0; }
    #year{ width: 4em; }
    #cal { width: 98%; border-collapse: collapse; margin-left: 1%; margin-right: 1%;}
    #cal td { border: 1px solid #999999; height: 8em; vertical-align: top; width: 14%; padding: 0}
    #today { background-color: #ffffcc; }
    div.day { text-align: right; color: #162fbd; background-color: #c3d9ff; padding-right: .5em; }
    div.event { border-bottom: 1px dotted #cccccc; text-align: left; padding: .25em; font-size: .75em; color: #666666;}
    hr {color: #999999; background-color: #999999; height: 1px; border: 0; }
    div.demo { background-color: #fad163; border-bottom: 1px solid #000000; margin-bottom: 1em; padding: .5em;}
    div.demo a { color: #000000; }
    a.edit { color: #999999; font-size: 90%; text-decoration: none;}
    a.edit:hover { text-decoration: underline;}
  </style>
  <style type="text/css" media="print">
    div.donotprint { display: none; }
  </style>
  <script type="text/javascript">
    <!--

      function validate() {
	  var valid = true;
	  var regex = /^[0-9]+\$/;

	  if (document.top.year.value == "" | document.bottom.year.value == "") {
             valid = false;
          }
	  var results = regex.exec(document.top.year.value);
	  var bottom = regex.exec(document.bottom.year.value);

	  if (results == null) {
	     valid = false;
	  }

	  if (bottom == null) {
	      valid = false;
          }
	  
	  if (valid == false) {
	      document.top.year.value = new Date().getFullYear();
	      document.bottom.year.value = new Date().getFullYear();
	  }

	  return true;
      }
    // -->
  </script>
</head>
<body>
HEADER

print "<div class=\"donotprint\">\n";
  print "<div style=\"float: left; width: 10em; text-align: left; margin-left: 1em;\"><a href=\"./?month=", $preMonth, "&year=", $preYear, "\">&lt; ", $months[$cleanMonth - 2], " ", $preYear, "</a></div>\n";
  print "<div style=\"float: right; width: 10em; text-align: right; margin-right: 1em;\"><a href=\"./?month=", $nextMonth, "&year=", $nextYear, "\">", $months[$nextMonth - 1], " ", $nextYear, " &gt;</a></div>\n";
  
  print "<form action=\"./\" method=\"get\" name=\"top\" onSubmit=\"return validate()\">\n";
  print "<select name=\"month\" id=\"month\">\n";
  
  for ($i = 0; $i < 12; $i++) {
      if ( $i == $cleanMonth - 1 ) {
	  print "<option value=\"", $i + 1, "\" selected=\"selected\">$months[$i]</option>\n";
      }
      else {
	  print "<option value=\"", $i + 1, "\">$months[$i]</option>\n";
      }
  }
  
  print "</select>\n";
  print "<input type=\"text\" name=\"year\" id=\"year\" value=\"$cleanYear\" />\n";
  print "<input type=\"submit\" value=\"Go\" />\n";
  print "</form>\n";
  
  print "<hr>\n";
  print "</div>\n";
  
  print "<h1>$cal[0]</h1>\n";

print <<TABLETOP;
<table id="cal">
<tr>
<th>Sunday</th>
<th>Monday</th>
<th>Tuesday</th>
<th>Wednesday</th>
<th>Thursday</th>
<th>Friday</th>
<th>Saturday</th>
</tr>
TABLETOP

for $i ( 2 .. $#cal ) {

    if ( $cal[$i] != '' ) {

	print "<tr>\n";
	
	$cal[$i] =~ s/(.{2})\s/\1\t/g;
	
	@day = split(/\t/, $cal[$i]);
    
	for $j ( 0 .. 6 ) {
	    print "<td";
	    if ( $day[$j] =~ m/\d+/ ) {
		
		$day[$j] =~ s/\s*//g;

		# build today
		($year) = (localtime(time))[5] + 1900;
		($mday) = (localtime(time))[3];
		($m)    = (localtime(time))[4] + 1;
		$today = $m . "-" . $mday . "-" . $year;

		# build string
		$string = $cleanMonth . "-" . $day[$j] . "-" . $cleanYear;

		if ( $today eq $string ) {
		    print " id = \"today\"";
		}
		
		print "><div class=\"day\">$day[$j]</div>";
		
		$events = $hash_of_events{$string};

		$i = 0;

		foreach $event (@$events) {
		    print "<div class=\"event\"><a href=\"javascript:var tmp=window.open('./view.cgi?id=$string&index=$i','View Event','toolbar=0,location=0,status=0,menubar=0,height=450px,width=550px')\" title=\"View Details\">$event</a> - <a href=\"javascript:var tmp=window.open('./edit.cgi?id=$string&index=$i','Edit Event','toolbar=0,location=0,status=0,menubar=0,height=450px,width=550px')\" class=\"edit\" title=\"Edit Event\">edit</a> - <a href=\"javascript:var tmp=window.open('./delete.cgi?id=$string&index=$i','Delete Event','toolbar=0,location=0,status=0,menubar=0,height=450px,width=550px')\" class=\"edit\" title=\"Delete Event\">del</a></div>";
		    $i++;
		}
		
		print "<div class=\"donotprint\">\n";
		print "<div style=\"float: center; text-align: left; margin-left: 1em;\">";
		print "<a href=\"javascript:var tmp=window.open('./add.cgi?id=$string','Add Event', 'toolbar=0,location=0,status=0,menubar=0,height=450px,width=550px')\" class=\"edit\" title=\"Add Event\">add</a>\n";
		print "</div></div></div>\n";

	    }
	    else {
		print ">$day[$j]";
	    }

	    print "</td>\n";
	}
	
	print "</tr>\n";
    }
}

print "</table>\n";
print "<br />\n";

print "<hr>\n";

  print "<div class=\"donotprint\">\n";
  print "<div style=\"float: left; width: 10em; text-align: left; margin-left: 1em;\"><a href=\"./?month=", $preMonth, "&year=", $preYear, "\">&lt; ", $months[$cleanMonth - 2], " ", $preYear, "</a></div>\n";
  print "<div style=\"float: right; width: 10em; text-align: right; margin-right: 1em;\"><a href=\"./?month=", $nextMonth, "&year=", $nextYear, "\">", $months[$nextMonth - 1], " ", $nextYear, " &gt;</a></div>\n";

  print "<form action=\"./\" method=\"get\" name=\"bottom\" onSubmit=\"return validate()\">\n";
  print "<select name=\"month\" id=\"month\">\n";

  for ($i = 0; $i < 12; $i++) {
      if ( $i == $cleanMonth - 1 ) {
          print "<option value=\"", $i + 1, "\" selected=\"selected\">$months[$i]</option>\n";
      }
      else {
          print "<option value=\"", $i + 1, "\">$months[$i]</option>\n";
      }
  }

  print "</select>\n";
  print "<input type=\"text\" name=\"year\" id=\"year\" value=\"$cleanYear\" />\n";
  print "<input type=\"submit\" value=\"Go\" />\n";
  print "</form>\n";
  print "</div>\n";


print <<FOOTER;
</body>
</html>
FOOTER



