//
// Created by aprice on 10/11/17.
//

#ifndef MYSILLYSHELL_ALIAS_H
#define MYSILLYSHELL_ALIAS_H

#include "../utils/myUtils.h"

struct alias
{
    char* aliasName;
    char* command;
};

typedef struct alias Alias;


void cleanTypeAlias(void * ptr);

void * buildTypeAlias(FILE* fin);

int compareAlias(const void * p1, const void * p2);



#endif //MYSILLYSHELL_ALIAS_H
