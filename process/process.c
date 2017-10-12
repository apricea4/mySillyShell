#include <wait.h>
#include "process.h"
#include "unistd.h"

void forkIt(char ** argv)
{
    pid_t pid = fork();
    int status;
    if(pid != 0)
    {
        waitpid(pid,&status,0);


    }
    else
    {
        execvp(argv[0],argv);
        exit(-1);

    }



}
