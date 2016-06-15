#! /usr/bin/perl -w

# author: Patrick Trinkle
# date:   3/11/2006
# course: CMSC433
# email:  tri1@umbc.edu

@xmlfiles = glob("*.xml");
@indexarray;
$counter = 0;

$/ = undef;

foreach $xmlfile (@xmlfiles) {
    
    open(IN, $xmlfile) or die "Failed to open xml file.\n";
    
    $xmlcontents = <IN>;

    $xmlfile =~ m/(\d+)\.xml/i;
    $filenumber = $1;

    if ( $xmlcontents =~ m/<filename>(.*)?<\/filename>/i ) {
	$imgfilename = $1;
    }

    if ( $xmlcontents =~ m/<title>(.*)?<\/title>/i ) {
	$imgtitle = $1;
    }

    if ( $xmlcontents =~ m/<location>(.*)?<\/location>/i ) {
	$imgloc = $1;
    }

    if ( $xmlcontents =~ m/<comments>(.*)?<\/comments>/si ) {
	$imgcomments = $1;
    }

    $indexarray[$counter] = [$filenumber, $imgtitle];

    close(IN) or die "Failed to close xml file.\n";

    open(IMG, "image-template.html") or die "Failed to open image-template.html .\n";

    $image_template = <IMG>;

    close(IMG) or die "Failed to close image-template.html .\n";

    $image_template =~ s/<% title %>/$imgtitle/gi;
    $image_template =~ s/<% filename %>/$imgfilename/gi;
    $image_template =~ s/<% location %>/$imgloc/gi;
    $image_template =~ s/<% comments %>/$imgcomments/gi;
    
    open(OUT, ">$filenumber.html");
    
    print OUT "$image_template";
    
    $counter++;
}

$link_list = "";

foreach $row_ref (@indexarray) {    
    $link_list .= "<li><a href=\"@$row_ref[0].html\">@$row_ref[1]</a></li>\n";
}

open(INDEX, "index-template.html") or die "Failed to open index-template.html .\n";

$index_template = <INDEX>;

close(INDEX) or die "Failed to close index-template.html .\n";

$index_template =~ s/<% links %>/$link_list/i;

open(INDEX_OUT, ">index.html") or die "Failed to open index.html .\n";

print INDEX_OUT $index_template;

close(INDEX_OUT) or die "Failed to close index.html .\n";

