all:	./main/cscd340Lab5.c ./tokenize/makeArgs.c ./process/process.c ./utils/myUtils.c ./utils/fileUtil.c ./pipes/pipes.c ./linkedlist/linkedList.c ./linkedlist/listUtils.c ./alias/alias.c
	gcc -Wall ./main/cscd340Lab5.c ./tokenize/makeArgs.c ./process/process.c ./utils/myUtils.c ./utils/fileUtil.c ./pipes/pipes.c ./linkedlist/linkedList.c ./linkedlist/listUtils.c ./alias/alias.c
