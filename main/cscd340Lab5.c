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

      Node* cur = aliasList->head;
      int found = 0;
      char tmpS[MAX];
      strcpy(tmpS,s);
      char** argList = NULL;
      int argListCount = makeargs(tmpS,&argList," ");
      Node * track = NULL;
      while(cur != NULL)
      {
          cur = cur->next;
          if(checkForAlias(argList,cur->data, argListCount)==1)
          {
              insertString(s,cur->data);


          }


      }
      if(found != 0)
      {

          //convertAlias(track->data);



      }
      clean(argListCount,argList);


      pipeCount = containsPipe(s);
      redirectCount = containsRedirect(s);

      char cdTmp[MAX];
      strcpy(cdTmp,s);
      if(strstr(cdTmp,"cd") != NULL)
      {

          char dir[MAX];
          int j = 0;
          for(int i =0; i<strlen(s); i++)
          {
              if(i>2)
              {
                  dir[j] = s[i];
                  j++;

              }

          }

          strip(dir);

          chdir(dir);

      }

      char aliasTmp[MAX];
      strcpy(aliasTmp,s);
      if(strstr(aliasTmp,"alias") !=NULL && strstr(aliasTmp,"=") !=NULL)
      {
          Node* nn = buildInputNode(s,buildInputAlias);
          //check if alias already exists, if it does then remove the old one
          addFirst(aliasList,nn);
          printList(aliasList,convertAlias);

      }


	if(pipeCount > 0 && redirectCount == 0)
	{
		prePipe = parsePrePipe(s, &preCount);
		postPipe = parsePostPipe(s, &postCount);
		pipeIt(prePipe, postPipe, NULL);
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
        strcpy(tmp,s);
        char** argv = NULL;
         int count = makeargs(tmp,&argv,"|");
        char* fileName = NULL;
        if(strstr(s,"<"))
        {
            //printf("prePipe, postPipe in < %s %s", prePipe[2], *postPipe);

            handleInPipe(argv);
        }
        else
        {
            char tmp[MAX];
            strcpy(tmp,s);
            prePipe = parsePrePipe(tmp,&preCount);
            char** prePostPipe = NULL;
            int c = makeargs(argv[1],&prePostPipe,">");
            fileName = prePostPipe[1];
            postCount = makeargs(prePostPipe[0],&postPipe," ");
            removeSpace(fileName);
            pipeIt(prePipe,postPipe,fileName);
            clean(c,prePostPipe);
            clean(preCount,prePipe);
            clean(postCount,postPipe);

        }
        clean(count, argv);


    }


    if(redirectCount>1 && pipeCount ==1)
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

