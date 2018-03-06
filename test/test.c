#include <ftmalloc.h>
// gcc test/test.c -o test0 -I inc -L . libft_malloc.so
int main()
{
	char *addr;

	addr = (char*)malloc(1024);
	show_alloc_mem();
	ft_printstr("\n==============\n\n");
	free(addr);
	return (0);
}
