#!/bin/bash
PATH=$(printenv PATH)
make fclean && gcc client.c -o client.exe && gcc server.c -o server.exe
./server.exe
