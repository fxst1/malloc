#!/bin/bash

rm -f libft_malloc*.so test0 test1 test2 test3 test4 test5
make -C ..
cp -f ../libft_malloc_TMP.so .
ln -sf libft_malloc_TMP.so libft_malloc.so

gcc -I ../inc test0.c -o test0
gcc -I ../inc test1.c -o test1
gcc -I ../inc test2.c -o test2
gcc -I ../inc test3_1.c -o test3_1
gcc -I ../inc test3_2.c -o test3_2
gcc -I ../inc test4.c -o test4
#gcc -I ../inc test5.c -o test5 -L . libft_malloc.so
