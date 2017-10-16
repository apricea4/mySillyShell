#include <wait.h>
#include "process.h"
#include "../utils/myUtils.h"
#include "../tokenize/makeArgs.h"
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



int containsRedirect(char* s)
{

    char tmp[MAX];
    char* save =NULL;
    strcpy(tmp,s);
    int count = -2;
    char* token = strtok_r(tmp,">",&save);
    while(token != NULL)
    {
        token = strtok_r(NULL, ">", &save);
        count++;


    }
    strcpy(tmp,s);
    token = strtok_r(tmp,"<",&save);
    while(token != NULL)
    {
        token = strtok_r(NULL, "<",&save);
        count++;
    }

    //printf("contains redirects %d",count);
    return count;

}

void redirectIt(char *s)
{

    char tmp[MAX];
    strcpy(tmp,s);
    char** argv = NULL;
    int argc = makeargs(tmp,&argv,"<");
    if(argc > 1)
    {
        handleIn(argv);
    }
    //printf("argc %d",argc);
    strcpy(tmp,s);
    char** argv2 = NULL;
    clean(argc,argv);
    argc = makeargs(tmp,&argv,">");

    if(argc > 1)
    {
        handleOut(argv);
    }
    clean(argc,argv);
    //printf("argc2 %d ", argc);


}


void handleOut(char** argv)
{

    int status;
    char ** command;

    int count = makeargs(argv[0], &command," ");
    pid_t pid = fork();
    if(pid == 0)
    {
        removeSpace(argv[1]);
        FILE *fout = fopen(argv[1],"w");
        int fileD = fileno(fout);

        close(1);
        dup(fileD);
        close(fileD);
        fclose(fout);
        if(execvp(command[0],command)<0)
        {
           exit(139);

        }
        else
        {
            waitpid(pid,&status,0);



            if(status == 139)
            {
                printf("unknown command %s", *command);

            }
            clean(count,command);

        }



    }






}


void handleIn(char** argv)
{
    int status;
    //FILE* fin = NULL;
    if(strcmp(argv[0],"0") == 0)
    {


    }



    char** command =NULL;
    int argc = makeargs(argv[0], &command, " ");
    pid_t pid = fork();
    if(pid == 0)
    {

        char tmp[MAX];

        strcpy(tmp,argv[1]);
        removeSpace(tmp);

        FILE* fin = fopen(tmp,"r");
        if(fin == NULL)
        {
            printf("null file \n");
            exit(EXIT_FAILURE);
        }
        int finD = fileno(fin);
        close(0);
        dup(finD);
        close(finD);
        fclose(fin);
        if(execvp(command[0],command)<0)
        {
            exit(139);
        }

    }
    else
    {
        waitpid(pid,&status,0);


        if(status == 139)
        {
            printf("command not found %s\n", *command);
        }
        clean(argc,command);


    }






}

