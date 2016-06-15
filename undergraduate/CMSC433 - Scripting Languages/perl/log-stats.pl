#! /usr/bin/perl -w

# author: Patrick Trinkle
# date:   3/11/2006
# course: CMSC433
# email:  tri1@umbc.edu

(@ARGV == 1) or die "You need to also give it an input file.\n";

my $inputfile = shift;

open(IN, $inputfile) or die "Could not open: $inputfile\n";

for $i (0 ... 23) {
    $hours[$i] = 0;
}

while (<IN>) {
    if ( m/\"(GET|POST) (.*?) /i ) {
        $resources{$2}++;
	
	if ( m/((\d{1,3}\.){3}\d{1,3})/ ) {
	    $ipaddrs{$1}++;
	}
	
	if ( m/\d{2}\/[a-z]{3}\/\d{4}:(\d{2}):\d{2}:\d{2}/i ) {
	    $hours[$1]++;
	}
	
	if ( m/\".+\" \"(.*)\"$/i ) {
	    $user_agents{$1}++;
	}
    }
}

close(IN) or die "Could not close: $inputfile\n";

# print hours.
print "\nRequests per Hour\n", "-" x 17, "\n";

for $i (0 ... $#hours) {
    printf("%02d:%14d\n", $i, $hours[$i]);
}

@ip_keys = sort { $ipaddrs{$b} <=> $ipaddrs{$a} } keys %ipaddrs;

@res_keys = sort { $resources{$b} <=> $resources{$a} } keys %resources;

@agent_keys = sort { $user_agents{$b} <=> $user_agents{$a} } keys %user_agents;

# begin sorting, then print top 10 of each

print "\nTop 10 User Agents\n", "-" x 18, "\n";

for $i (0 ... 9) {
    printf("%2d", $i + 1);
    print ": $agent_keys[$i] ($user_agents{$agent_keys[$i]} requests)\n";
}

print "\nTop 10 Requested Resources\n", "-" x 26, "\n";

for $i (0 ... 9) {
    printf("%2d", $i + 1);
    print ": $res_keys[$i] ($resources{$res_keys[$i]} requests)\n";
}

print "\nTop 10 Requesters\n", "-" x 17, "\n";

for $i (0 ... 9) {
    printf("%2d", $i + 1);
    print ": $ip_keys[$i] ($ipaddrs{$ip_keys[$i]} requests)\n";
}

print "\n";
