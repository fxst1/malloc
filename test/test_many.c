#include <ftmalloc.h>
//#include <stdio.h>
#define ALLOC_S 1
//#define MAXALLOC 16777215
#define MAXALLOC 4

static void			*alloc(size_t len)
{
	void			*addr;
	size_t			i;

	i = 0;
	addr = malloc(len);
	if (addr)
		while (i < len)
		{
			((unsigned char*)addr)[i] = i;
			i++;
		}
	return (addr);
}

int					main(int argc, char **argv)
{
	size_t			size;
	size_t			i;
	void			**tests;

	tests = (void**)malloc(sizeof(void*) * MAXALLOC);
	if (!tests)
	{
		//printf("Cannot allocate buffer\n");
		return (0);
	}

	i = 0;
	size = (argc > 1) ? (size_t)atoi(argv[1]) : ALLOC_S; 
	while (i < MAXALLOC - 2)
	{
		//printf("alloc %zu\n", i);
		tests[i] = alloc(size);
		i++;
		//printf("end\n");
	}

	while (i < MAXALLOC)
	{
		//printf("alloc %zu\n", i);
		tests[i] = malloc(4096);
		i++;
		//printf("end\n");
	}	

	//if (size <= 256)
		show_alloc_dbg(FTMALLOC_SHOW_AREA | FTMALLOC_SHOW_BLOCK | FTMALLOC_SHOW_WASTE | FTMALLOC_SHOW_FREE, RUSAGE_SELF);

	i = 0;
	while (i < MAXALLOC)
	{
		free(tests[i]);
		i++;
	}
	free(tests);
	show_alloc_dbg(FTMALLOC_SHOW_ALL, RUSAGE_SELF);

	return (0);
}
