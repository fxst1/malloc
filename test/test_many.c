#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <ftmalloc.h>
#define ALLOC_S 1
//#define MAXALLOC 16777215
#define MAXALLOC 4

void			*alloc(size_t len)
{
	void			*addr;
	size_t			i;

	i = 0;
	addr = malloc(len);
	if (addr)
	{
		while (i < len)
		{
			((unsigned char*)addr)[i] = i;
			i++;
		}
	}
	return (addr);
}

void 				handler(int s)
{
	int	fd = open("segfault", O_WRONLY | O_CREAT, 0644);
	int nfd = dup2(1, fd);
	show_alloc_mem();
	close(fd);
	close(nfd);
	(void)s;
	(void)nfd;
}

int					main(int argc, char **argv)
{
	size_t			size;
	size_t			max;
	size_t			i;
	void			**tests;

	signal(SIGSEGV, handler);

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
//	if (size <= 256)
//		show_alloc_dbg(FTMALLOC_SHOW_AREA | FTMALLOC_SHOW_BLOCK | FTMALLOC_SHOW_WASTE | FTMALLOC_SHOW_FREE, RUSAGE_SELF);
	i = 0;
	while (i < max)
	{
		free(tests[i]);
		i++;
	}
	free(tests);
	ft_printstr("=================\n");
	show_alloc_mem();
//	show_alloc_dbg(FTMALLOC_SHOW_ALL, RUSAGE_SELF);
	return (0);
}
