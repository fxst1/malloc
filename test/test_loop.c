#include <ftmalloc.h>
#include <stdio.h>
# define ALLOC_S 1

int					main(int argc, char **argv)
{
	size_t			size;
	size_t			i;
	unsigned char	*addr;

	i = 0;
	size = (argc > 1) ? (size_t)atoi(argv[1]) : ALLOC_S; 
#ifndef NOFT
	write(STDOUT_FILENO, "malloc(", 7);
	ft_printnum(size);
	write(STDOUT_FILENO, ")", 1);
#endif
	addr = (unsigned char*)malloc(sizeof(unsigned char) * size);
#ifndef NOFT
	write(STDOUT_FILENO, " = ", 3);
	ft_printhex((intptr_t)addr, -1, 1);
	write(STDOUT_FILENO, "\n", 1);
#endif
	if (addr)
		while (i < size)
		{
			addr[i] = i;
			i++;
		}
#ifndef NOFT
	if (size <= 256)
		show_alloc_dbg(FTMALLOC_SHOW_ALL, RUSAGE_SELF);
#endif
	while (1)
		;
	return (0);
}
