#!/bin/bash
export DYLD_LIBRARY_PATH=:libft_malloc_x86_64_Linux.so #MAC
export LD_PRELOAD=:libft_malloc_x86_64_Linux.so #Linux (prefered)
export LD_LIBRARY_PATH=:libft_malloc_x86_64_Linux.so #Linux
echo Starting $@
$@
