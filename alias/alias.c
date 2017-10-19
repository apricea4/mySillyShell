
#include "alias.h"
#include "../tokenize/makeArgs.h"
#include "../linkedlist/linkedList.h"


int checkForAlias(char** s, void* data, int argc)
{
    Alias* al = (Alias*)data;
    for(int i =0; i< argc; i++)
    {

        if(strcmp(s[i],al->aliasName) ==0)
        {
            return 1;
        }


    }
    return 0;




}

char** compareAliasLineIn(const char* lineIn, LinkedList* aliasList)
{

    Node* cur = aliasList->head;
    while(cur != NULL)
    {

        cur = cur-> next;
        Alias* al = (Alias*)cur->data;
        if(strcmp(lineIn,al->aliasName)==0)
        {




        }

    }



}








void * buildTypeAlias(FILE* fin)
{

    char tmp[MAX];
    fgets(tmp,MAX,fin);
    strip(tmp);
    int argc = 0;
    char** aliasParts = NULL;
    argc = makeargs(tmp, &aliasParts,"=");
    removeQuotes(aliasParts[1]);
    Alias* al = (Alias*)calloc(1, sizeof(Alias));
    char* save = NULL;
    char* token = strtok_r(aliasParts[0]," ", &save);
    token = strtok_r(NULL," ",&save);

    al->aliasName = (char*)calloc(strlen(token)+1,sizeof(char));
    strcpy(al->aliasName,token);
    al->command = (char*)calloc(strlen(aliasParts[1])+1,sizeof(char));
    strcpy(al->command,aliasParts[1]);
    clean(argc,aliasParts);
    //free(aliasParts);
    aliasParts = NULL;
    return al;



}


void* buildInputAlias(char * s)
{
    char tmp[MAX];
    strcpy(tmp,s);
    strip(tmp);
    int argc = 0;
    char** aliasParts = NULL;
    argc = makeargs(tmp, &aliasParts,"=");

    Alias* al = (Alias*)calloc(1, sizeof(Alias));
    char* save = NULL;
    char* token = strtok_r(aliasParts[0]," ", &save);
    token = strtok_r(NULL," ",&save);
    removeQuotes(aliasParts[1]);
    al->aliasName = (char*)calloc(strlen(token)+1,sizeof(char));
    strcpy(al->aliasName,token);
    al->command = (char*)calloc(strlen(aliasParts[1])+1,sizeof(char));
    strcpy(al->command,aliasParts[1]);
    clean(argc,aliasParts);
    //free(aliasParts);
    aliasParts = NULL;
    return al;






}

void convertAlias(void* ptr)
{

    Alias *al = (Alias*)ptr;
    printf("command: %s\n alias %s\n",al->command, al->aliasName);

}

void cleanTypeAlias(void* ptr)
{

    Alias* al = (Alias*)ptr;

    free(al->aliasName);
    free(al->command);
    free(al);
    al = NULL;





}