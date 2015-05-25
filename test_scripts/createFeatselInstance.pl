#!/usr/bin/perl -w

# createFeatselInstance.pl -- creates a RANDOM_ABS_SUM XML featsel instance.
#
# M.S.Reis, Aug.19.2010

use strict;
use POSIX qw(ceil floor);

#
# Main code
#

@ARGV == 2 or die "\nError: you must specify the number of elements and the maximum value of an element!\n\n";

my $n = $ARGV[0];
my $MAX = $ARGV[1];
my @S; 

$S[$_] = int(rand($MAX)) foreach 1..$n;

my $sum = 0;

$sum += $S[$_] foreach 1..$n;

my $t = int(rand($sum));

# Produces the XML
#
printf STDOUT "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
printf STDOUT "<ElementSet>\n  <SetName> $t </SetName>\n";
printf STDOUT "  <MaxNumberOfElementValues> 1 </MaxNumberOfElementValues>\n";
printf STDOUT "  <NumberOfElements> $n </NumberOfElements>\n";

foreach(1..$n){
  printf STDOUT "  <Element>\n    <name>e$_</name>\n";
  printf STDOUT "    <value> %d  </value>\n  </Element>", $S[$_];
}

printf STDOUT "</ElementSet>\n";
