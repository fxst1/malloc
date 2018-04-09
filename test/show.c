#include <ftmalloc.h>
#include <stdio.h>

int		main(void)
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1);
		addr[0] = 42;
		i++;
	}
	show_alloc_mem();
	printf("%p\n", addr);
	return (0);
}
