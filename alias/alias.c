
#include "alias.h"
#include "../tokenize/makeArgs.h"

void * buildTypeAlias(FILE* fin)
{

    char tmp[MAX];
    fgets(tmp,MAX,fin);
    strip(tmp);
    char** aliasParts = NULL;
    makeargs(tmp, &aliasParts,"=");

    Alias* al = (Alias*)calloc(1, sizeof(Alias));
    char* save;
    char* token = strtok_r(aliasParts[0]," ", &save);
    token = strtok_r(NULL," ",&save);

    al->aliasName = (char*)calloc(strlen(token)+1,sizeof(char));
    strcpy(al->aliasName,token);
    al->command = (char*)calloc(strlen(aliasParts[1])+1,sizeof(char));
    strcpy(al->command,aliasParts[1]);
    return al;



}
