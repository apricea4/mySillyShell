#include "../pipes/pipes.h"
#include "../utils/myUtils.h"
#include "../utils/fileUtil.h"
#include "../process/process.h"
#include "../tokenize/makeArgs.h"
#include "../linkedlist/listUtils.h"
#include "../alias/alias.h"
int main()
{
	int histCount = 100;
	int histFileCount = 1000;
    int pathListSize = 0;
    int redirectCount = 0;
	LinkedList* aliasList = linkedList();//free
	char** pathList = NULL;//free
  int argc, pipeCount;	
  char **argv = NULL, s[MAX];
  int preCount = 0, postCount = 0;
  char ** prePipe = NULL, ** postPipe = NULL;

	FILE* Fmsshrc = NULL;
	Fmsshrc = fopen(".msshrc","r");
	if(Fmsshrc != NULL)
	{
		pathList = handleRc(&histCount,&histFileCount,Fmsshrc,aliasList,pathList, &pathListSize);

	}
	else
	{
		printf("no file found next to executable, using defaults\n");
	}






  printf("command?: ");
  fgets(s, MAX, stdin);
  strip(s);

  while(strcmp(s, "exit") != 0)
  {
      pipeCount = containsPipe(s);
      redirectCount = containsRedirect(s);

	if(pipeCount > 0 && redirectCount == 0)
	{
		prePipe = parsePrePipe(s, &preCount);
		postPipe = parsePostPipe(s, &postCount);
		pipeIt(prePipe, postPipe);
		clean(preCount, prePipe);
        	clean(postCount, postPipe);
	}// end if pipeCount

    if(redirectCount == 1 && pipeCount == 0)
    {
        redirectIt(s);


    }
    if(pipeCount > 0 && redirectCount == 1)
    {
        char tmp[MAX];
        char* save;
        strcpy(tmp,s);
        char** argv = NULL;
         int count = makeargs(tmp,&argv,"|");
        postPipe = parsePostPipe(s,&postCount);
        if(strstr(s,"<"))
        {
            //printf("prePipe, postPipe in < %s %s", prePipe[2], *postPipe);

            handleInPipe(argv);
        }
        else
        {
            //handleOutPipe(s)

        }


    }


    if(redirectCount>0 && pipeCount > 0)
    {
        prePipe = parsePrePipe(s, &preCount);
        postPipe = parsePostPipe(s,&postCount);








    }
	else if(pipeCount == 0 && redirectCount == 0)
	{
		argc = makeargs(s, &argv," ");
	  	if(argc != -1)
	  		forkIt(argv);
	  
	  	clean(argc, argv);
	  	argv = NULL;
	}
	
	printf("command?: ");
	fgets(s, MAX, stdin);
      	strip(s);

  }// end while

    //TODO:CLEAN UP MEMORY LEAK



    //clean(pathListSize,pathList);
    clearList(aliasList,cleanTypeAlias);
    free(aliasList);
  return 0;

}// end main

