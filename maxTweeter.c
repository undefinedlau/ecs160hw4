#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Tweeter
{
   char name[20];
   int count;
};

// initialize all counts in array to be 0 and all names to be empty
void initTweeters(struct Tweeter tweeters[20000])
{
	for (int i = 0; i < 20000; i++)
	{
		strcpy(tweeters[i].name, "");
		tweeters[i].count = 0;
	}
}

// checks if the file exists (if it does not exist then it is not a valid file)
void verifyInputFile(FILE *fp)
{
	// if file is cannot be found then report and exit
	if (fp == NULL)
	{
		//printf("HERE1\n");
		printf("Invalid Input Format\n");
		exit(-1);
	}
}

// get the number of commas and the index of "name" column
int getCommaIndexOfHeaders(int* header_comma_count, FILE *fp)
{
	char line[1024];
	char *found;

	fgets(line, 1024, fp);
	int csv_pos = 0, index_of_tweeter = -1; // used to get name column
	char *string = line;

	// this for loop grabs the number of commas in the header
	for (int i = 0; i < strlen(string); i++)
		if (string[i] == ',')
				(*header_comma_count)++;

	if (*header_comma_count == 0)
	{
		printf("Invalid Input Format\n");
		exit(-1);
	} // a valid csv file needs to have commas, duh

	// loop through each token to find "name" column
	while( (found = strsep(&string,",")) != NULL )
	{
		// find column index with tweeter names
		//if (strcmp(found, "name") == 0 || strcmp(found, "name\n") == 0)
		if (strcmp(found, "name") == 0 || strcmp(found, "name\n") == 0 || strcmp(found, "\"name\"") == 0 || strcmp(found, "\"name\"\n") == 0)
			index_of_tweeter = csv_pos;

		csv_pos++;
	}

	if (index_of_tweeter == -1)
	{
		//printf("HERE2\n");
		printf("Invalid Input Format\n");
		exit(-1);
	} // if the header does not contain a "name" field

	return index_of_tweeter;
} // returns index_of_tweeter (name) and the header_comma_count

// get the names and the number of tweets to populate array of tweeter structs
void populateTweeterArray(struct Tweeter tweeters[20000], FILE *fp, int index_of_tweeter, int *header_comma_count)
{
	char *string, *found;
	char line[1024];
	int csv_pos = 0, line_comma_count = 0;

	// loop through each line of the file
	while (fgets(line, 1024, fp))
	{
		line_comma_count = 0;
		csv_pos = 0;	// reset csv_pos for each line
		string = line; // IDK WHY BUT WE HAVE TO DO IT LIKE dis

		// this for loop grabs the number of commas in the tweeter lines
		for (int i = 0; i < strlen(string); i++)
			if (string[i] == ',')
					line_comma_count++;

		// test if # of commas in line is same as # commas in header
		if (line_comma_count != *header_comma_count)
		{
			//printf("HERE3\n");
			printf("Invalid Input Format\n");
			exit(-1);
		}

		// strsep adapted from http://c-for-dummies.com/blog/?p=1769
		// loop through each token; used strsep bc strtok skips empty entries
	  while( (found = strsep(&string,",")) != NULL )
		{
			// if we are the column that has the "name" of the tweeter
			if (csv_pos == index_of_tweeter)
			{
				// loop through array of tweeters
				for (int i = 0; i < 20000; i++)
				{
					// if name DNE in tweeters array already, add it
					if (strlen(tweeters[i].name) == 0)
					{
						strcpy(tweeters[i].name, found);
						tweeters[i].count++;
						break;
					}
					// if name exists, increase count
					if (strcmp(tweeters[i].name, found) == 0)
					{
						tweeters[i].count++;
						break;
					}
				}
			}
			csv_pos++;
		}
	}
}

void copyTweeters(struct Tweeter tweeters[20000], struct Tweeter tmpTweeters[20000])
{
	for (int i = 0; i < 20000; i++)
	{
		strcpy(tmpTweeters[i].name, tweeters[i].name);
		tmpTweeters[i].count = tweeters[i].count;
	}
} // make a copy of tweeters

// find the tweeters that tweet the most
void getMaxTweeters(struct Tweeter maxTweeters[10], struct Tweeter tmpTweeters[20000])
{
	int max = 0;
	int index_of_max = 0;

	// loop 10 times to find top 10
	for (int i = 0; i < 10; i++)
	{
		max = 0;

		// find the max tweeter, note index, and set count to 0 so it is not max anymore
		for (int j = 0; j < 20000; j++)
		{
			if (strlen(tmpTweeters[j].name) != 0)
			{
				if (tmpTweeters[j].count > max)
				{
					index_of_max = j;
					max = tmpTweeters[j].count;
					tmpTweeters[j].count = 0;
				}
			}
		}

		if (max == 0) // if we sadly cannot find a max
			break;

		strcpy(maxTweeters[i].name, tmpTweeters[index_of_max].name); // populate the maxTweeters array
		maxTweeters[i].count = max;
	}
} // does as function name says

// print at most top ten tweeters
void printMax(struct Tweeter maxTweeters[10])
{
	for (int i = 0; i < 10; i++)
	{
		if (maxTweeters[i].count != 0) // only print out the max (for cases in which we have <10 tweeters)
			printf("%s: %d\n", maxTweeters[i].name, maxTweeters[i].count);
	}
}


int main(int argc, char** argv)
{
	int index_of_tweeter = -1, csv_pos = 0, *header_comma_count, line_comma_count = 0;
	struct Tweeter tweeters[20000], maxTweeters[10], tmpTweeters[20000];

	header_comma_count = malloc(sizeof(int));
	*header_comma_count = 0;
	FILE *fp = fopen(argv[1], "r");

	verifyInputFile(fp);
	initTweeters(tweeters);
	index_of_tweeter = getCommaIndexOfHeaders(header_comma_count, fp);
	populateTweeterArray(tweeters, fp, index_of_tweeter, header_comma_count);
	copyTweeters(tweeters, tmpTweeters);
	getMaxTweeters(maxTweeters, tmpTweeters);
	printMax(maxTweeters);
	free(header_comma_count);

	fclose(fp);

	return 0;
}
