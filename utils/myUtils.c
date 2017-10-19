#include "myUtils.h"
void removeSpace(char *ar)
{


	int j =0;
	for(int i =0; i<strlen(ar); i++)
	{
        ar[i - j] = ar[i];
		if(ar[i] == ' ')
		{


            j++;
		}




	}
    ar[strlen(ar)-j] = '\0';


	strip(ar);


}

void removeQuotes(char* ar)
{



	int j =0;
	for(int i =0; i<strlen(ar); i++)
	{
		ar[i - j] = ar[i];
		if(ar[i] == '"')
		{


			j++;
		}




	}
	ar[strlen(ar)-j] = '\0';


	strip(ar);




}




void insertString(char* s, void* alias)
{
	Alias* al = (Alias*)alias;

	char tmpRead[MAX];

	strcpy(tmpRead,s);
	char* removable = strstr(tmpRead,al->aliasName);
	u_long startPosition = removable - tmpRead;
	printf("start position %lu", startPosition);
	char* left = NULL;
	char* right = NULL;
	left = makeLeftString(tmpRead,startPosition);
	right = makeRightString(tmpRead,strlen(al->aliasName) + startPosition,strlen(s));
	strcat(left,al->command);
	//printf("after first cat %s", left);
	strcat(left,right);

	//printf("after second cat %s", left);
	strcpy(s,left);
    free(left);
    free(right);


}

char* makeLeftString(char* from, u_long start)
{

    char * into = calloc(MAX,sizeof(char));

		for(u_long i =0; i< start; i++)
		{
			into[i] = from[i];


		}
    return into;

}

char* makeRightString(char* from, u_long start, u_long end)
{
    char* right = calloc(MAX,sizeof(char));
    int j =0;
    for(u_long i = start; i<end; i++)
    {
        right[j] = from[i];
        j++;

    }
    return right;



}


void strip(char *array)
{
	if(array == NULL)
	{
		perror("array is null");
		exit(-99);
	}// end if

	int len = strlen(array), x = 0;

	while(array[x] != '\0' && x < len)
	{
	  if(array[x] == '\r')
		 array[x] = '\0';

	  else if(array[x] == '\n')
		 array[x] = '\0';

	  x++;

}// end while

}// end strip

int menu()
{
   char temp[MAX];
   int choice;
   printf("1) Print the list - Word\n");
   printf("2) Add First - Word\n");
   printf("3) Add Last - Word\n");
   printf("4) Sort - Word\n");
   printf("5) Remove First - Word\n");
   printf("6) Remove Item - Word\n");
   printf("============================\n");
   printf("7) Print the list - Movie\n");
   printf("8) Add First - Movie\n");
   printf("9) Add Last - Movie\n");
   printf("10) Remove Last - Movie\n");
   printf("11) Remove Item - Movie\n");
   printf("12) Quit\n");
   printf("Choice --> ");
   fgets(temp, MAX, stdin);
   choice = atoi(temp);


   while(choice < 1 || choice > 12)
   {
   	printf("1) Print the list - Word\n");
   	printf("2) Add First - Word\n");
   	printf("3) Add Last - Word\n");
   	printf("4) Sort - Word\n");
	printf("5) Remove First - Word\n");
   	printf("6) Remove Item - Word\n");
	printf("============================\n");
   	printf("7) Print the list - Movie\n");
   	printf("8) Add First - Movie\n");
   	printf("9) Add Last - Movie\n");
	printf("10) Remove Last - Movie\n");
   	printf("11) Remove Item - Movie\n");
   	printf("12) Quit\n");
   	printf("Choice --> ");
   	fgets(temp, MAX, stdin);
   	choice = atoi(temp);

   }// end while

   return choice;

}// end menu

