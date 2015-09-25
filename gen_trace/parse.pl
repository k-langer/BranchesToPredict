#!/usr/bin/perl

use strict;
use warnings;

my $out = ""; 
while (my $line = <>) {
    #print $line;
    chomp($line); 
    if ($line =~ /=/) {
        if ( $line =~ /\=>\s(0x[\d\w]*).*:\s+(\w+)/) {
            $out =  "$1   $2";
        }
        if ($line =~ /\s=\s(\d+)/) {    
            if ($1 > 0) {
            print "$out   $1\n";
            }
        }
    } 
}


#if ( $row =~ /initial.*readmem/) { $insideCmt = 0; }

