
#           Jitendra Kumar 
#          1401CS19
#           Assignment : lab_8
#           date :  29 . 03 . 2016


#!/usr/bin/perl

sub edit_dist 
{

	#Storing two strings
	my ($s1, $s2) = @_;
	my ($len1, $len2) = (length $s1, length $s2);

   
	my %mat;

	for (my $i = 0; $i <= $len1; ++$i)
	{
		for (my $j = 0; $j <= $len2; ++$j)
		{
	   	 	$mat{$i}{$j} = 0;
	    		$mat{0}{$j} = $j;
		}

		$mat{$i}{0} = $i;
    	}

    	my @ar1 = split(//, $s1);
    	my @ar2 = split(//, $s2);

    	for (my $i = 1; $i <= $len1; ++$i)
    	{
		for (my $j = 1; $j <= $len2; ++$j)
		{
	 
	    		my $cost = ($ar1[$i-1] eq $ar2[$j-1]) ? 0 : 1;

	  
			$mat{$i}{$j} = min([$mat{$i-1}{$j} + 1, $mat{$i}{$j-1} + 1, $mat{$i-1}{$j-1} + $cost]);
		}
    	}
	return $mat{$len1}{$len2};
}

#sub-routine to get the minimum of three arguments
sub min
{
    	my @list = @{$_[0]};
    	my $min = $list[0];

    	foreach my $i (@list)
    	{
		$min = $i if ($i < $min);
    	}

    	return $min;
}



#Checking for similar words of incorrect spelling
sub similarCheck
{
    
    
    	$w=@_[0];
    	shift(@_);
    	@list=@_;
    	$curr=100;
    	@final=undef;
    	foreach $q(@list)
    	{
	
		chomp($q);
       		$l=edit_dist(lc $q,lc $w);
       
       		if($l<$curr)
       		{
	    		$curr=$l;
	    		@final=undef;
	    		push(@final,$q);
       		}
       		elsif($l==$curr)
       		{
	    		push(@final,$q);
       		}
      		 else
       		{
       
       		}
       
       
    	}
    	$fi=join(',', @final);
    	print " - $fi\n";
}


#opening file
open(DATA,"</usr/share/dict/words") or die "Can't open the dictionary";
@dictwords=<DATA>;

#To flag if no mistakes are found
$f=0;
# starting the  display on terminal 
print "*********************************************************************************************************************************";
print "\n---------------------------------------------------Welcome to Spell Checker------------------------------------------------------\n";
print "*********************************************************************************************************************************\n";

#take input from user
print "Enter the string to check spelling:\n";
$inline=lc <STDIN>;
@inwords=split(/ /,$inline);

print "\nMisspelled words in the input and the similar words in dictionary are: \n";
print "------------------------------------------------------------------------\n";
foreach $a(@inwords)
{

    	chomp($a);
    	unless(grep( /^$a$/, @dictwords) )
    	{
		print "$a";
		$f=1;
		print "\n";
		similarCheck($a,@dictwords);
    	}
}
if($f==0)
{
    	print "No spelling mistake found in the inputted string\n";
}
print "-------------------------------------------------------------------------\n";


close(DATA);
print "*********************************************************************************************************************************";
print "\n---------------------------------------------------Thank you for using spellchecker----------------------------------------------\n";
print "*********************************************************************************************************************************\n";
#end