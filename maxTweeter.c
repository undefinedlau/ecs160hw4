#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int index_of_tweeter = -1, csv_pos = 0;
	char c;
	FILE* fp;
	fp = fopen(argv[1], "r");
	char line[1024];
	char *found, *string;

	// test if path does not exist and exit if it doesn't
	if (fp == NULL)
	{
		printf("Invalid Input Format\n");
		exit(-1);
	}

	// get each line from file and split according to token
	while (fgets(line, 1024, fp))
	{
		csv_pos = 0;	// reset csv_pos for each line
		string = line; // IDK WHY BUT WE HAVE TO DO IT LIKE dis

		// strsep adapted from http://c-for-dummies.com/blog/?p=1769
	  while( (found = strsep(&string,",")) != NULL )
		{
			// find column index with tweeter names
			if (strcmp(found, "name") == 0)
			{
				index_of_tweeter = csv_pos;
				csv_pos++;	// increment csv_pos

				continue;
			}

			// check to see if we are in the names columns
			if (csv_pos == index_of_tweeter)
				printf("%s\n", found);


			csv_pos++;
		}
	}

	free(string);
	return 0;

}
