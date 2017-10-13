#include "fileUtil.h"
#include "myUtils.h"
#include "../alias/alias.h"
#include "../tokenize/makeArgs.h"
#include "../linkedlist/listUtils.h"
#include "../linkedlist/linkedList.h"

FILE * openInputFile_Prompt()
{
   char temp[100];
   printf("Please enter the name of the input file ");
   fgets(temp, 100, stdin);
   strip(temp);
   FILE * fin = fopen(temp, "r");

   while(fin == NULL)
   {
      printf("Please enter the name of the input file ");
      fgets(temp, 100, stdin);
      strip(temp);
      fin = fopen(temp, "r");
   }// end while

   return fin;
}// end openInputFile_Prompt

FILE * openInputFileType_Prompt(char * type)
{
   char temp[100];
   printf("Please enter the name of the %s input file ", type);
   fgets(temp, 100, stdin);
   strip(temp);
   FILE * fin = fopen(temp, "r");

   while(fin == NULL)
   {
      printf("Please enter the name of the input file ");
      fgets(temp, 100, stdin);
      strip(temp);
      fin = fopen(temp, "r");
   }// end while

   return fin;
}// end openInputFileType_Prompt

int countAlias(FILE * fin)
{

    char tmp[MAX];
    int count = 0;
    fgets(tmp, MAX,fin);//get rid of space between env vars and alias list
    fgets(tmp, MAX,fin);
    while(strncmp(tmp,"alias", strlen("alias")) == 0)
    {
        count++;
        fgets(tmp,MAX,fin);


    }
    rewind(fin);


}



void handleRc(int* histCount, int* histFileCount, FILE* fin, LinkedList* aliasList, LinkedList* pathList)
{

    char tmp[MAX];
    fgets(tmp,MAX,fin);
    strip(tmp);
    if(strncmp(tmp,"HISTCOUNT",strlen("HISTCOUNT")) == 0)
    {
        char ** envVar = NULL;
        makeargs(tmp,&envVar,"=");
        *histCount = atoi(envVar[1]);
        clean(2,envVar);
        fgets(tmp,MAX,fin);
        strip(tmp);
        makeargs(tmp, &envVar,"=");
        *histFileCount = atoi(envVar[1]);

        clean(2,envVar);
        envVar = NULL;

    }

    else
    {
        char ** envVar = NULL;
        makeargs(tmp,&envVar,"=");
        *histFileCount = atoi(envVar[1]);
        fgets(tmp,MAX,fin);
        strip(tmp);
        makeargs(tmp, &envVar,"=");
        *histCount = atoi(envVar[1]);
        clean(2,envVar);
        envVar = NULL;



    }

    int i = 0;
    int aliasCount = countAlias(fin);
    fgets(tmp,MAX,fin);//run through histcount and filecount
    fgets(tmp,MAX,fin);
    fgets(tmp,MAX,fin); //get rid of space between env vars and alias
    while(i<aliasCount)
    {

        Node * nn = buildNode(fin,&buildTypeAlias);
        addFirst(aliasList,nn);
        aliasCount++;



    }
    //now build path 2d array
    fgets(tmp,MAX,fin);//skip the blank line




    fclose(fin);








}




int countRecords(FILE * fin, int linesPerRecord)
{
	if(fin == NULL || linesPerRecord <= 0)
	{
		perror("fin is null or linesPerRecord<=0");
		exit(-99);
	}// end if

   int count = 0;
   char temp[MAX];
   fgets(temp, MAX, fin);
   while(!feof(fin))
   {
      count ++;
      fgets(temp, MAX, fin);

   }// end while

   if(count == 0)
   {
   		perror("count is 0");
   		exit(-99);
   }// end if

   rewind(fin);
   return count / linesPerRecord;
}// end count records


int readTotal(FILE * fin)
{
	if(fin == NULL)
	{
		perror("fin is null");
		exit(-99);
	}// end if

	int total;
	char temp[MAX];
	fgets(temp, MAX, fin);

	total = atoi(temp);
	if(total <= 0)
	{
		perror("total is <= 0");
		exit(-99);
	}// end if

	return total;

}// end readTotal


