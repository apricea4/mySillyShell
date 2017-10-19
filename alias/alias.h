//
// Created by aprice on 10/11/17.
//

#ifndef MYSILLYSHELL_ALIAS_H
#define MYSILLYSHELL_ALIAS_H

#include "../utils/myUtils.h"
#include "../linkedlist/linkedList.h"

struct alias
{
    char* aliasName;
    char* command;
};

typedef struct alias Alias;


void cleanTypeAlias(void * ptr);

void * buildTypeAlias(FILE* fin);

char** compareAliasLineIn(const char* lineIn, LinkedList* aliasList);

void* buildInputAlias(char* s);

void convertAlias(void*ptr);

int checkForAlias(char** s, void* data, int argc);


#endif //MYSILLYSHELL_ALIAS_H
