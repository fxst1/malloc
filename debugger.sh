#!/bin/bash
echo Debugging $@
gdb -iex "set exec-wrapper env LD_PRELOAD=./libft_malloc_x86_64_Linux.so env LD_LIBRARY_PATH=libft_malloc_x86_64_Linux.so" $1
