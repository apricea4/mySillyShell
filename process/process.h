#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void forkIt(char ** argv);

int containsRedirect(char* s);

void redirectIt(char *s);

void handleIn(char** argv);

void handleOut(char** argv);

void handleOutPipe(char** pre);

void  handleInPipe(char** pre);

#endif
