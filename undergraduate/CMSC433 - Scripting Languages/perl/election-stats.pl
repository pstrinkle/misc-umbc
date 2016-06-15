#! /usr/bin/perl -w

# author: Patrick Trinkle
# date:   3/11/2006
# course: CMSC433
# email:  tri1@umbc.edu

# -t := print states by total number of votes in descending order
# -r := print states sorted by the percentage of overall votes which were Republican in descending order
# -d := the Democrat Option

use Getopt::Std;

# call getopts, pass in reference to opts hash
getopts('trd', \%opts);

(@ARGV == 1) or die "You need to also give it an input file.\n";

my $inputfile = shift;
my $count = 0;
my @info;
my @sorted;

open(IN, $inputfile) or die "Could not open: $inputfile\n";

while(<IN>)
{
    if (! m/\s*#/ ) {

	if (m/([a-z]{2}):(\d*):(\d*):\d*:\d*:\d*:(\d*)/i) {
	    
	    $rpercent = 100 * ($2 / $4);
	    $dpercent = 100 * ($3 / $4);
	    
	    $info[$count] = ( {'state' => $1, 'r' => $rpercent, 'd' => $dpercent, 'total' => $4} );
	
	    $count++;
	}
    }
}

close(IN);

if (defined($opts{'t'})) {
    @sorted = sort totalsort @info;
}
elsif (defined($opts{'r'})) {
    @sorted = sort repubsort @info;
}
elsif (defined($opts{'d'})) {
    @sorted = sort demosort @info;
}
else
{
    print "You need to specify either a -t to sort by state totals,";
    print "-r or -d for sorting by republicans or democrats\n";
}

print "State\tTotal Votes\t% Republicans\t% Democrats\n", "-" x 51, "\n";

for $i ( 0 .. $#sorted ) {
    print $sorted[$i]{state};
    print " " x 6;
    printf ("%11d", $sorted[$i]{total});
    print " " x 12;
    printf ("%5.2f%%", $sorted[$i]{r});
    print " " x 8;
    printf ("%5.2f%%", $sorted[$i]{d});
    print "\n";
}

sub repubsort {

    if ( $$a{r} > $$b{r} ) {
	return (-1);
    }
    elsif ( $$a{r} < $$b{r} ) {
	return (1);
    }
    return (0);
}

sub demosort {

    if ( $$a{d} > $$b{d} ) {
	return (-1);
    }
    elsif ( $$a{d} < $$b{d} ) {
	return (1);
    }
    return (0);
}

sub totalsort{

    if ( $$a{total} > $$b{total} ) {
	return (-1);
    }
    elsif ( $$a{total} < $$b{total} ) {
	return (1);
    }
    return (0);
}
