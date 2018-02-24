#include <ftmalloc.h>
#include <stdio.h>
#define ALLOC_S 1	

int					main(int argc, char **argv)
{
	size_t			size;
	size_t			i;
	unsigned char	*addr;

	i = 0;
	size = (argc > 1) ? (size_t)atoi(argv[1]) : ALLOC_S; 
	write(STDOUT_FILENO, "malloc(", 7);
	mem_printnum(size);
	write(STDOUT_FILENO, ")", 1);
	addr = (unsigned char*)malloc(sizeof(unsigned char) * size);
	write(STDOUT_FILENO, " = ", 3);
	mem_printaddr((intptr_t)addr, -1, 1);
	write(STDOUT_FILENO, "\n", 1);
	if (addr)
		while (i < size)
		{
			addr[i] = i;
			i++;
		}
	if (size <= 256)
		show_alloc_dbg(FTMALLOC_SHOW_ALL, RUSAGE_SELF);
	return (0);
}
