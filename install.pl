#!/bin/perl
# ^^^^^^^^^ 
# CUSTOMIZE THIS TO POINT TO YOUR PERL BINARY!!!!
#
# WatCH installation script
# Time-stamp: <Paul Sanschagrin -- Tue Jul 17 09:38:37 EDT 2001>
#
# to run: ./install.pl

use Cwd;
$perl = $^X;
$current_dir = cwd();
system "mkdir $current_dir/bin";

# unpack the Perl scripts and change the path to the perl binary
open IN, $current_dir."/perl/perl_scripts";

print "\n*** extracting Perl scripts ***\n";
while ( <IN> )
{
    if ( /^____FILE\_START/ )
    {
	chop;
	# grep the name of packed Perl script
	@line = split;
	$file = "$current_dir/bin/$line[1]";
	open OUT, ">$file" or die "Can't \n";
	# read the line that includes the path to the Perl binary
	$_ = <IN>;
	print OUT "\#\!$perl\n";
	next;
    }
    if ( /^____FILE\_END/ )
    {
	# end of this script, close filehandle and change permissions
	close OUT;
	chmod 0755, "$file";
	next;
    }
    print OUT $_;
}
close IN;

# compile WatCH
chdir "$current_dir/src";
print "\n*** compiling  ***\n\n";
system "make";
system "mv cluster $current_dir/bin";
system "make clean";

# copy the run script, with the addition of the installation directory
$sed_dir = $current_dir;
$sed_dir =~ s/\//\\\//g;
system "sed 's/DIRECTORY/$sed_dir\\/bin/g' prep_WatCH > ".
  "$current_dir/bin/prep_WatCH";
system "chmod +x $current_dir/bin/prep_WatCH";


print "\n*** installation completed ***\n";
print "\n\n*** Please see license.txt for licensing and use information ***\n\n";
