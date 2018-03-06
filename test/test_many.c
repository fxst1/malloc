#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <ftmalloc.h>
#define ALLOC_S 1
//#define MAXALLOC 16777215
#define MAXALLOC 4

void 			init_alloc(void *addr, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		((unsigned char*)addr)[i] = 42;
		i++;
	}
}

void			*alloc(size_t len)
{
	void			*addr;

	addr = malloc(len);
	if (addr)
		init_alloc(addr, len);
	return (addr);
}

int					main(int argc, char **argv)
{
	size_t			size;
	size_t			max;
	size_t			i;
	void			**tests;

	size = (argc > 1) ? (size_t)atoi(argv[1]) : ALLOC_S;
	max = (argc > 2) ? (size_t)atoi(argv[2]) : MAXALLOC;
	tests = (void**)malloc(sizeof(void*) * max);
	if (!tests)
	{
		//printf("Cannot allocate buffer\n");
		return (0);
	}

	i = 0;
	while (i < max)
	{
		tests[i] = alloc(size);
		i++;
	}

	show_alloc_mem();
	i = 0;
	while (i < max)
	{
		free(tests[i]);
		i++;
	}
	free(tests);
	ft_printstr("=================\n");
	show_alloc_mem();
	return (0);
}
