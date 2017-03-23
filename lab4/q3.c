
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, char* argv[])
{

	if(argc != 3)
	{
		printf("required input format : ./a.out pattern_to_be_found name_of_the_file \n");
		exit(-1);
	}

	FILE* file = fopen(argv[2], "r");
	if (file == NULL)
	{
		printf("File doesn't exist or can't be loaded !\n");
		exit(-2);
	}

	char* LINE = malloc(sizeof(char)*512);
	if(LINE == NULL)
	{
		perror("Internal-Memory Error: ");
		exit(-3);
	}

	int number_of_lines_found = 0;
	int reading_the_line = 0;
	
	while(!feof(file))
	{
		
		fgets(LINE, sizeof(char)*512, file);
		if(strcasestr(LINE, argv[1]) != NULL)
		{
			printf("Line: %d::%s",reading_the_line, LINE);
			number_of_lines_found += 1;
		}
		reading_the_line += 1;
		free(LINE);
		LINE = malloc(sizeof(char)*512);
		if(LINE == NULL)
		{
			perror("Internal-Memory Error: ");
			exit(-4);
		}		
	}
	printf("\n");

	if(number_of_lines_found == 0)
	{
		printf("Found no occurance of the pattern in the file: %s\n", argv[2]);
		exit(0);
	}
	else
	{
		printf("Found %d occurance(s) of the pattern given in the file %s\n", number_of_lines_found, argv[2]);
		exit(0);
	}


}