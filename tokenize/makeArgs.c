#include "makeArgs.h"

void clean(int argc, char **argv)
{


	for(int i = 0; i<argc; i++)
	{
		free(argv[i]);
		argv[i] = NULL;


	}
	free(argv);



}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv)
{

	char copy[MAX];
	strcpy(copy, s);

	char *savePtr;
	int count = 0;




	char *token = strtok_r(s," ", &savePtr);
	while(token != NULL)
	{
		count++;
		token = strtok_r(NULL," ", &savePtr);


	}

	if(count <= 0)
	{
		return -1;

	}

	(*argv) = (char**)calloc(count+1, sizeof(char*));
	token = strtok_r(copy," ",&savePtr);
	strip(token);
	(*argv)[0] = (char*)calloc(strlen(token)+1,sizeof(char));
	strcpy((*argv)[0],token);
	for(int i = 1; i<count; i++)
	{
		token = strtok_r(NULL," ", &savePtr);
		strip(token);
		(*argv)[i] = (char*)calloc(strlen(token)+1,sizeof(char));
		strcpy((*argv)[i],token);

	}
	return count;

}// end makeArgs
