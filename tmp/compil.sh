#!/bin/bash

rm -f libft_malloc_x86_64_Linux.so libft_malloc.so
make -C ..
cp -f ../libft_malloc_x86_64_Linux.so .
ln -sf libft_malloc_x86_64_Linux.so libft_malloc.so

gcc -I ../inc test0.c -o test0
gcc -I ../inc test1.c -o test1
gcc -I ../inc test2.c -o test2
gcc -I ../inc test3.c -o test3
gcc -I ../inc test4.c -o test4
gcc -I ../inc test5.c -o test5 -L . libft_malloc.so
