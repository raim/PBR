#!/usr/local/bin/perl

my $file="DATA";
my $cnt=1;
my $fh;
while(<>) {
    if ( /Time/ ) {
	open($fh, ">", $file.$cnt.".txt");
	$cnt++;
    }
    print $fh $_;    
}
