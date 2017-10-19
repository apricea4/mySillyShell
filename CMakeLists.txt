cmake_minimum_required(VERSION 3.8)
project(shell)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main/cscd340Lab6.c ./tokenize/makeArgs.c ./utils/myUtils.c ./process/process.c ./pipes/pipes.c
        ./linkedlist/linkedList.c ./linkedlist/listUtils.c ./utils/fileUtil.c ./utils/myUtils.c ./alias/alias.c)
add_executable(shell ${SOURCE_FILES})
