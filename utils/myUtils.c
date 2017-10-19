#include "myUtils.h"
void removeSpace(char *ar)
{
	char tmp[MAX];

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

	char tmp[MAX];

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
	char tmpWrite[MAX];
	strcpy(tmpRead,s);
	char* removable = strstr(tmpRead,al->aliasName);
	u_long startPosition = removable - tmpRead;
	printf("start position %lu", startPosition);
	char left[MAX];
	char right[MAX];
	makeSubString(left,tmpRead,startPosition+1,strlen(s));
	makeSubString(tmpWrite,tmpRead,strlen(al->aliasName) + startPosition,strlen(s));
	strcat(left,al->command);
	printf("after first cat %s", left);
	strcat(left,tmpWrite);
	printf("after second cat %s", left);
	strcpy(s,left);
	printf("is it that easy? %s\n",s);

}

void makeSubString(char* into, char* from, u_long start, u_long end)
{



		for(u_long i =0; (i+start)-1< end; i++)
		{
			into[i] = from[(start + i)];


		}







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

