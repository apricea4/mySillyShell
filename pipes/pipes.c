#include "pipes.h"
#include "../tokenize/makeArgs.h"

int containsPipe(char *s)
{
    char* save;
    char copy[MAX];
    char* res = NULL;
    strcpy(copy,s);
    res = strtok_r(copy,"|",&save);
    if(res == NULL)
    {
        return -1;
    }

    int i = -1;
    while(res != NULL)
    {

        res = strtok_r(NULL,"|",&save);
        ++i;

    }
    //printf("contains pipe %d ", i);
    return i;




}
char ** parsePrePipe(char *s, int * preCount)
{

    char delim[3] = " ";
    char* save;
    char copy[MAX];
    strcpy(copy,s);
    char* prePipe = strtok_r(copy,"|",&save);
    strip(prePipe);


    //printf("prePipe-> %s\n", prePipe );

    char** pre = NULL;
    *preCount = makeargs(prePipe, &pre, delim);

    return pre;





}
char ** parsePostPipe(char *s, int * postCount)
{
    char* save;
    char copy[MAX];
    char delim[3] = " ";
    strcpy(copy,s);
    char* postPipe = strtok_r(copy,"|",&save);
    postPipe = strtok_r(NULL, "|", &save);
    //printf("postPipe-> %s\n", postPipe );



    char** post = NULL;
    *postCount = makeargs(postPipe, &post, delim);

    return post;




}




void pipeIt(char ** prePipe, char ** postPipe, char* fileName)
{

    pid_t pid = fork();
    int status;

    int fd[2];
    pipe(fd);



    //printf("pre post %s %s \n", *prePipe, *postPipe);
    if(pid == 0)//if child of a.out
    {
        pid_t pid2 = fork();
        if(pid2 == 0) //grandchild aka ls-l execute first
        {
            close(fd[0]);
            close(1);
            dup(fd[1]);
            close(fd[1]);
            if(execvp(prePipe[0], prePipe) < 0)
            {

		        _Exit(EXIT_FAILURE);

		
            }

        }

        else //parent of ls -l
        {

            waitpid(pid2, &status,0);

            if(status == 256)
            {
                printf("command not found: %s\n",*prePipe);
                exit(-1);
            }
            if(fileName != NULL)
            {
                FILE* fout = fopen(fileName,"w");

                if(fout != NULL)
                {
                    int fileD = fileno(fout);
                    close(1);
                    dup(fileD);
                    close(fileD);
                    close(fd[1]);
                    close(0);
                    dup(fd[0]);
                    close(fd[0]);
                    fclose(fout);
                    if(execvp(postPipe[0], postPipe) < 0)
                    {
                        printf("command not found file %s\n",*postPipe);
                        exit(-1);

                    }

                }

            }

            /*;*/
            close(fd[1]);
            close(0);
            dup(fd[0]);
            close(fd[0]);
            //fclose(fout);
            if(execvp(postPipe[0], postPipe) < 0)
            {
                printf("command not found post pipe %s\n",*postPipe);
                exit(-1);

            }


        }






    }
    else
    {

        waitpid(pid,&status,0);


    }


}


