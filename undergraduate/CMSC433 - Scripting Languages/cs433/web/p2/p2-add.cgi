#!/usr/bin/perl -w

# Name: Patrick Trinkle
# Course: CMSC433
# Project: P2
# Email: tri1@umbc.edu
# File: add.cgi

$ENV{PATH} = "/usr/bin";

use CGI;
use CGI::Carp qw(fatalsToBrowser);

# build web content
print "Content-type: text/html\n\n";

print <<HEADER;
<html>
  <head>
  <title>Add Event</title>
  <link rel="stylesheet" type="text/css" href="style.css" />
<script type="text/javascript">
          <!--

    function validateForm() {

	var valid = true;

	if (document.getElementById("name").value == "") {
          document.getElementById("name").style.border = '1px solid #ff0000';
	  valid = false;
	}

        var regex = /^[0-9]{1,2}-[0-9]{1,2}-[0-9]{4}\$/;
	var regexcap = /^([0-9]{1,2})-([0-9]{1,2})-([0-9]{4})\$/;

	if (document.getElementById("date").value == "") {
          document.getElementById("date").style.border = '1px solid #ff0000';
	  valid = false;
        }
	
	var results = regex.exec(document.getElementById("date").value);

        if (results == null) {
	  document.getElementById("date").style.border = '1px solid #ff0000';
          valid = false;
	}

	var test = regexcap.test(document.getElementById("date").value);

	if (test) {
	  var month = RegExp.\$1;
	  var day = RegExp.\$2;
	  var year = RegExp.\$3;
	}

	if (valid == false) {
          document.getElementById("valid").innerHTML = '<span style="color: #ff0000;">There have been some errors!</span>';
	}

	return valid;
    }
          // -->
        </script>
</head>
<body>
HEADER

# the events file
$file = "/afs/umbc.edu/users/t/r/tri1/pub/cs433/read-write/events.dat";

# check to see if there's a url thing
$query = new CGI;

$id = $query->param('id');

print "<div class=\"form\">\n";
print "<h1>Add Event</h1>\n";
print "<div id=\"valid\"></div>\n";

if ( !$query->param('name') ) { 

print <<EVENT;
<form action="add.cgi" method="post" onSubmit="return validateForm()">
    <table>
        <tr>
            <td class="label"><label for="name">Name<sup>&#8224;</sup>:</label></td>
            <td class="input"><input id="name" name="name" value="" /></td>
        </tr>
        <tr>
            <td class="label"><label for="date">Date:</label></td>
            <td class="input"><input id="date" name="date" value="$id" /></td>
        </tr>
        <tr>
            <td class="label" valign="top"><label for="details">Details:</label></td>
            <td class="input"><div><textarea id="details" name="details"></textarea></div></td>
        </tr>
        <tr>
            <td colspan="2"><sup>&#8224;</sup> Denotes required field</td>
        </tr>
        <tr>
            <td class="buttons" colspan="2">
                <input type="button" value="Cancel" onclick="javascript:window.close();"/>
                <input type="submit" value="Add Event" style="font-weight: bold" />
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
    $details = $query->param('details');

    $details =~ s/</&lt;/g;
    $details =~ s/>/&gt;/g;
    $name =~ s/</&lt;/g;
    $name =~ s/>/&gt;/g;

    if ($details eq "") {
	$details = " ";
    }

    # add it to file

    open(OUTFILE, ">> $file");

    print OUTFILE "$date $name \"$details\"\n";

    close(OUTFILE);

    print "<p>Successfully added event</p>\n";
    print "<p><a href=\"javascript:window.close();\">Close Window</a></p>";
}

print "</div>\n";

print <<FOOTER;
</body>
</html>
FOOTER
