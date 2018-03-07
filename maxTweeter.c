#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	char c;
	FILE* fp;
	fp = fopen(argv[1], "r");
	char line[1024];			// longest length in csv file is 459, so to be safe, we set to 1024 for now

	// test if path does not exist and exit if it doesn't
	if (fp == NULL)
	{
		printf("Invalid Input Format\n");
		exit(-1);
	}

	// get each line from file and split according to token
	while (fgets(line, 1024, fp))
	{
		char *token = strtok(line, ",");

		while (token != NULL)
		{
			printf("%s\n", token);
			token = strtok(NULL, ",");
		}
	}

	return 0;

}






/*
//while ((somechar = getline(&line, &len, fp) != 1))
//	printf("%s", line); // this chunk stops when it encounters a new line

c = fgetc(fp);
while (c != EOF)
{
	printf("%c", c);
	c = fgetc(fp);
} // this prints the entire file

printf("\n");
fclose(fp);
*/
