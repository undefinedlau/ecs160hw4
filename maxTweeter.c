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
	/*
	char** line;

	line = (char**)malloc(sizeof(char*)*1024);
	 for(int i=0; i<1024; i++)
	 {
			ptr[i] = (char*)malloc(sizeof(char)*1024);

	 }
	 */


	// test if path does not exist and exit if it doesn't
	if (fp == NULL)
	{
		printf("Invalid Input Format\n");
		exit(-1);
	}
	//printf("%lu\n", sizeof(line));


	// get each line from file and split according to token
	while (fgets(line, 1024, fp))
	{
		csv_pos = 0;

		string = line; // IDK WHY BUT WE HAVE TO DO IT LIKE dis
	  // printf("Original string: '%s'\n",string);

		// strsep adapted from http://c-for-dummies.com/blog/?p=1769
	  while( (found = strsep(&string,",")) != NULL )
		{
	      printf("%d: %s\n",csv_pos, found);
				csv_pos++;
		}

	}

	free(string);
	return 0;

}

/*
while (fgets(buf, BUFSIZE, fp) != NULL) {
    char *line  = buf;
    char *field;
    int index = 0;
    while ((field = strsep(&line, "|")) != NULL) {
        note the trailing field will contain newline.
        printf("element %d = %s\n", index, field);
        index++;
   }
}
*/





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
