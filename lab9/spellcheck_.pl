#---------------------------------------------------------------------------------------------------------------------
#           Jitendra Kumar 
#           1401CS19
#           Assignment : lab_9
#           date :  5 . 04 . 2016
#--------------------------------------------------------------------------------------------------------------------


#!/usr/bin/perl

# Module used to compute minimum number out of a set
use List::Util qw(min);

# uniq sub-rotine checks each element of the array and returns only unique ones.
sub uniq 
{
    	my %seen;
    	grep !$seen{$_}++, @_;
}

# Calculate min distance between the words
sub distance 
{
    	my ($str1, $str2) = @_;
    	my @ar1 = split( //, $str1);
    	my @ar2 = split( //, $str2);

    	my @dist;
    	foreach (0 .. @ar1)        { $dist[$_][0] = $_ } ;
    	foreach (0 .. @ar2)        { $dist[0][$_] = $_ } ;

    	foreach my $i (1 .. @ar1)
    	{
        		foreach my $j (1 .. @ar2)
        		{
            			my $cost = $ar1[$i - 1] eq $ar2[$j - 1] ? 0 : 1;
    	    		$dist[$i][$j] = min(   $dist[$i - 1][$j] + 1,   $dist[$i][$j - 1] + 1,  $dist[$i - 1][$j - 1] + $cost );
        		}
    	}
	return $dist[@ar1][@ar2];
}
#-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Open dictionary file
open(DICT,  "</usr/share/dict/words")  or die "Can't open my dictionary: $!";

# Initialize dictionary hash table
my %dict;

while (<DICT>)
{     
	chomp;
	# assigns each line in turn to $_ and add it to the Hash
	$dict{"$_"}= 0;
}

# Close the buffer when it's done
close DICT or die "Error : $!";



# Read Text from the file specified
open FILE, "$ARGV[0]";

@words;           # Array containing all the unique words to be checked against dictionary

# For every line in the given test file loop
while (<FILE>) 
{

	my $text = $_;
	chomp $text;
	$text =~ s/[[:punct:]]//g;                   #  Remove puctuations
	$text = lc $text;
	my @text1=split(/ /,$text);
	  
	foreach (@text1) { push(@words, $_); } # get all the words in the @words array
}

@words = uniq(@words); # Make the array elements unique , remove the duplicate elements .
print "--------------------------------------------------------------------------------------------------------------------------------\n";
print "---------------------------------------------------Welcome to Spell Checker-----------------------------------------------------\n";
print "\n printing the missspelled words one by one and corresponding similar words... \n \n";

# Loop on each word
foreach (@words)
{

    	# Check if word exists in the dictionary hash
	
	if (!(exists $dict{$_}))
	{

        	# Get and store the word and its length
        	my $spell = $_;
	my $spell_len = length $spell;
   	print "\t".$spell . "\t:\t ";

        	# Searching for similar words 
        	
	        	foreach(%dict)
	        	{

	            	# Compute the difference in length
	            	my $this_len = length $_;
		my $diff = $spell_len - $this_len;

		            	# Compute the distances of close length words , I have considered  the  distance  of 1 .
		            	# this will dramatically improve the performance
		            	if(abs($diff) <= 1)
		            	{
		                		if(distance($_, $spell) <= 1)
		                		{
		                			print $_.", "; 
		                		}
		            	}            
        		}
        	print " \n\n";
	}
}
print "\n---------------------------------------------------Thank you for using spellchecker---------------------------------------------\n";
print "--------------------------------------------------------------------------------------------------------------------------------\n";
#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------